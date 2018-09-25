
// Filament detector - uses input (microswitch, opto, hall-e etc.) to detect filament absence
// and control the 3dprinter suspend state by smoothie console comands

// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

#define SENSOR_PIN D5
#define LED_PIN D0

bool filamentState ;
bool msgCode = false ;

unsigned long previousMillis = 0;

// constants won't change:
const long interval = 3000;

Bounce debouncer = Bounce(); // Instantiate a Bounce object

void setup() {

  Serial.begin(115200);

  debouncer.attach(SENSOR_PIN, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncer.interval(300); // Use a debounce interval of 300 milliseconds

  filamentState = digitalRead(SENSOR_PIN);     // read the input pin
  pinMode(LED_PIN, OUTPUT); // Setup the LED
  digitalWrite(LED_PIN, filamentState);

}

void loop() {

  debouncer.update(); // Update the Bounce instance

  if ( debouncer.rose() ) {  // Call code if button transitions from LOW to HIGH
    Serial.println();
    Serial.println("M117");
    filamentState = HIGH; // Toggle LED state
    digitalWrite(LED_PIN, filamentState); // Apply new LED state
  }
  if ( debouncer.fell() ) {  // Call code if button transitions from HIGH to LOW
    Serial.println();
    Serial.println("suspend");
    filamentState = LOW; // Toggle LED state
    digitalWrite(LED_PIN, filamentState); // Apply new LED state
  }
  if (filamentState == LOW) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      // save the last time you send M117 message
      previousMillis = currentMillis;
      if (msgCode == false){
        Serial.println("M117 PLEASE CHANGE SPOOL");
        msgCode = true ;
      }else {
        Serial.println("M117 OUT OF FILAMENT");
        msgCode = false ;
      }
    }
  }
}

