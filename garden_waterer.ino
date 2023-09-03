#include "plant.h"

Plant jade(A0, 3, 480);

void setup() {
    Serial.begin(9600);
}

void loop() {
    jade.setMoistureLevel(); // get moisture levels
    Serial.print(jade.getMoistureLevel());
    Serial.println();
    delay(3000);
    
    jade.waterIfNeeded();
    // delay 8 hours
    // delay(1000 * 60 * 60 * 8); // ms * sec * min * hrs
}