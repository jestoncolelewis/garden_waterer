int analogPin = A0; // input pin for moisture detector
int moistureLevel = 0; // initialize moisture level

void setup() {
    Serial.begin(9600);
}

void loop() {
    moistureLevel = analogRead(analogPin); // get moisture levels
    Serial.print(moistureLevel);
    delay(10000);
    
    // if (moistureLevel > 350) { // if moisture levels are below desired level
      // start pump
      // delay(1000 * 60 * 5); // ms * sec * min
      // stop pump
    // }
    // delay 8 hours
    // delay(1000 * 60 * 60 * 8); // ms * sec * min * hrs
}