// nodeM esp8266 serial Filament controller 
// - use 2 inputs (microswitch, opto, hall-e etc.) to detect filament 
//   absence and control the 3dprinter suspend state by serial comand
// - semi-automatic filament changing
//      *slide filament into spool sensor for automatic nozzle heatup (slide out to cooldown)
//      *when heated up slide the filament into extruder sensor so it can be auto-loaded 
// 
// by protoDEV

// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

#define SPOOL_PIN D6
#define EXTRUDER_PIN D5
#define LED_PIN D0

bool spoolState ;
bool extruderState ;
byte state ;
bool preheatState = false;
bool msgCode = false ;
bool msgCode2 = false ;

unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;

// constants won't change:
const long interval  = 3000;

Bounce spoolSensor = Bounce(); // Instantiate a Bounce object
Bounce extruderSensor = Bounce(); // Instantiate a Bounce object

void setup() {

  Serial.begin(115200);

  spoolSensor.attach(SPOOL_PIN, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  spoolSensor.interval(300); // Use a debounce interval of 300 milliseconds

  extruderSensor.attach(EXTRUDER_PIN, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  extruderSensor.interval(2000); // Use a debounce interval of 3 seconds

  spoolState = digitalRead(SPOOL_PIN);     // read the input pin
  extruderState = digitalRead(EXTRUDER_PIN);     // read the input pin
  pinMode(LED_PIN, OUTPUT); // Setup the LED
  state = stateIndicator();
}
byte stateIndicator() {

  byte state;
  bool led = false;

  if ( (spoolState == HIGH) && (extruderState == HIGH) )
  {
    led = true;
    state = 3 ; // filament fully loaded
  }
  if ( (spoolState == LOW) && (extruderState == HIGH) )
  {
    state = 2 ; // filament loaded only in extruder sensor
  }
  if ( (spoolState == HIGH) && (extruderState == LOW) )
  {
    state = 1 ; // filament loaded only in spool sensor
  }
  if ( (spoolState == LOW) && (extruderState == LOW) )
  {
    state = 0 ; // filament not loaded
  }

  digitalWrite(LED_PIN, led); // Apply new LED state

  return state ;
}

void spoolLoop()  {

  if ( spoolSensor.rose() ) {  // Call code if button transitions from LOW to HIGH
    Serial.println("\nM117");
    if ( (state == 0) && (preheatState == LOW) )  {
      preheatState = HIGH; //Toggle Preheat state ON
      Serial.println("\nM104 S220");
    }
    spoolState = HIGH; // Toggle LED ON state
  }

  if ( spoolSensor.fell() ) {  // Call code if button transitions from HIGH to LOW
    //    Serial.println();
    if (preheatState == HIGH) {
      preheatState = LOW;
      Serial.println("\nM104 S0\nM117");
    }
    if (state == 3) {
      Serial.println();
      Serial.println("suspend");
    }
    spoolState = LOW; // Toggle LED OFF state
  }

}

void extruderLoop()  {

  if ( extruderSensor.rose() ) {  // Call code if button transitions from LOW to HIGH
    if ((state == 1) && (preheatState == HIGH)) {
      preheatState = LOW ;
      Serial.println("\nM117\nM120\nG91\nG1 E80 F300\nM121\nM400\nM104 S0");
    }
    extruderState = HIGH; // Toggle state
  }

  if ( extruderSensor.fell() ) {  // Call code if button transitions from HIGH to LOW
    extruderState = LOW; // Toggle state
  }

}

void messageLoop()  {

  unsigned long currentMillis = millis();

  if ( (state == 0) || (state == 2) ) {
    if (currentMillis - previousMillis >= interval) {
      // save the last time you send M117 message
      previousMillis = currentMillis;
      if (msgCode == false) {
        Serial.println("\nM117 PLEASE CHANGE SPOOL");
        msgCode = true ;
      } else {
        Serial.println("\nM117 OUT OF FILAMENT");
        msgCode = false ;
      }
    }
  }

  if ((state == 1) && (preheatState == HIGH)) {
    if (currentMillis - previousMillis2 >= interval) {
      // save the last time you send M117 message
      previousMillis2 = currentMillis;
      if (msgCode2 == false) {
        Serial.println("\nM117 WAIT FOR HEAT UP");
        msgCode2 = true ;
      } else {
        Serial.println("\nM117 THEN INSERT FILAMENT");
        msgCode2 = false ;
      }
    }
  }

}

void loop() {

  spoolSensor.update(); // Update the Bounce instance
  extruderSensor.update(); // Update the Bounce instance
  state = stateIndicator();
  spoolLoop();
  extruderLoop();
  messageLoop();

}

