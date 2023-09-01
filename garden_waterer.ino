int analogPin = A0; // input pin for moisture detector
int moistureLevel = 0; // initialize moisture level
int outputPin = 3;

void setup() {
    Serial.begin(9600);
    pinMode(analogPin, INPUT);
    pinMode(outputPin, OUTPUT);
}

void loop() {
    moistureLevel = analogRead(analogPin); // get moisture levels
    Serial.print(moistureLevel);
    Serial.println();
    delay(3000);
    
    if (moistureLevel > 480) { // while moisture levels are below desired level
      digitalWrite(outputPin, HIGH); // start pump
      delay(1000 * 60 * 5); // ms * sec * min
      digitalWrite(outputPin, LOW); //stop pump
    }
    // delay 8 hours
    delay(1000 * 60 * 60 * 8); // ms * sec * min * hrs
}