#include "plant.h"

unsigned long startMillis = millis();
unsigned long eightHours = 1000 * 60 * 60 * 8;

Plant jade(A0, 3, 480); // plant object

void setup() {
    Serial.begin(9600);
}

void loop() {
    jade.setMoistureLevel(); // set moisture levels
    Serial.print(jade.getMoistureLevel());
    Serial.println();
    delay(3000);
    
    // jade.waterIfNeeded();
    
    // while (millis() - startMillis < eightHours); // delay 8 hours
}