
// Filament detector - uses input (microswitch, opto, hall-e etc.) to detect filament absence
// and control the 3dprinter suspend state by smoothie console comands

// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

#define SPOOL_PIN D6
#define EXTRUDER_PIN D5
#define LED_PIN D0

bool spoolState ;
bool extruderState = false;
bool preheatState = false;
bool msgCode = false ;
bool msgCode2 = false ;

String strTmp = "suspend";

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
  extruderSensor.interval(3000); // Use a debounce interval of 3 seconds

  spoolState = digitalRead(SPOOL_PIN);     // read the input pin
  pinMode(LED_PIN, OUTPUT); // Setup the LED
  digitalWrite(LED_PIN, spoolState);

}

void spoolLoop()  {

  if ( spoolSensor.rose() ) {  // Call code if button transitions from LOW to HIGH
    Serial.println();
    Serial.println("M117");
    if (preheatState == LOW)  {
      Serial.println("M109 S220");
      preheatState = HIGH; //Toggle Preheat state ON
    }
    spoolState = HIGH; // Toggle LED ON state
    digitalWrite(LED_PIN, spoolState); // Apply new LED state
  }
  if ( spoolSensor.fell() ) {  // Call code if button transitions from HIGH to LOW
    Serial.println();
    if (preheatState == HIGH) {
      strTmp = "M104 S0";
    }
    Serial.println(strTmp);
    preheatState = LOW;
    strTmp = "suspend";
    spoolState = LOW; // Toggle LED OFF state
    digitalWrite(LED_PIN, spoolState); // Apply new LED state
  }
  if (spoolState == LOW) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      // save the last time you send M117 message
      previousMillis = currentMillis;
      if (msgCode == false) {
        Serial.println("M117 PLEASE CHANGE SPOOL");
        msgCode = true ;
      } else {
        Serial.println("M117 OUT OF FILAMENT");
        msgCode = false ;
      }
    }
  }
}

void extruderLoop()  {

  if ( extruderSensor.rose() ) {  // Call code if button transitions from LOW to HIGH
    if (preheatState == HIGH) {
      Serial.println();
      Serial.println("M117\nM120\nG91\nG1 E100 F300\nM121\nM400\nM104 S0\n");
      preheatState = LOW ;
    }
    extruderState = HIGH; // Toggle state
  }
  if ( extruderSensor.fell() ) {  // Call code if button transitions from HIGH to LOW
    extruderState = LOW; // Toggle state
  }
  if ((spoolState == HIGH) && (preheatState == HIGH)) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis2 >= interval) {
      // save the last time you send M117 message
      previousMillis2 = currentMillis;
      if (msgCode2 == false) {
        Serial.println("M117 HEATED UP");
        msgCode2 = true ;
      } else {
        Serial.println("M117 LOAD FILAMENT");
        msgCode2 = false ;
      }
    }
  }
}



void loop() {

  spoolSensor.update(); // Update the Bounce instance
  extruderSensor.update(); // Update the Bounce instance
  spoolLoop();
  extruderLoop();


}

