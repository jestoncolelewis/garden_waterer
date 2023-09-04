#include "plant.h"

unsigned long startMillis = millis();
Plant jade(A0, 3, 480); // plant object

void setup() {
    Serial.begin(9600);
}

void loop() {
    jade.setMoistureLevel(); // set moisture levels
    Serial.print(jade.getMoistureLevel());
    Serial.println();
    delay(3000);
    
    jade.waterIfNeeded();
    // delay 8 hours
    while (millis() - startMillis < 1000 * 60 * 60 * 8);
}