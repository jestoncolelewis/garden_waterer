int analogPin = A0; // input pin for moisture detector
int moistureLevel = 0; // initialize moisture level

void setup() {
    Serial.begin(9600);
}

void loop() {
    moistureLevel = analogRead(analogPin); // get moisture levels
    Serial.print(moistureLevel);
    Serial.println();
    delay(3000);
    
    // while (moistureLevel > 480) { // while moisture levels are below desired level
      // start pump
    // }
    // delay 8 hours
    // delay(1000 * 60 * 60 * 8); // ms * sec * min * hrs
}