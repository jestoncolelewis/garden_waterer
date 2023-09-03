#include "plant.h"

Plant jade(A0, 3, 0, 480);

void setup() {
    Serial.begin(9600);
}

void loop() {
    jade.setMoistureLevel(); // get moisture levels
    Serial.print(jade.getMoistureLevel());
    Serial.println();
    delay(3000);
    
    if (jade.getMoistureLevel() > jade.getDrynessLimit()) { // while moisture levels are below desired level
      digitalWrite(jade.getOutput(), HIGH); // start pump
      delay(1000 * 60); // * 5); // ms * sec * min
      digitalWrite(jade.getOutput(), LOW); //stop pump
    }
    // delay 8 hours
    // delay(1000 * 60 * 60 * 8); // ms * sec * min * hrs
}