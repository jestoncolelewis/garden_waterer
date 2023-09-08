#include "plant.h"

unsigned long eightHours = 1000 * 60 * 60 * 8;

Plant jade(A0, 2, 480); // plant object

void setup() {
    Serial.begin(9600);
    jade.setOutput(jade.getOutput());
    digitalWrite(jade.getOutput(), HIGH);
    jade.setInput(jade.getInput());
}

void loop() {
    jade.setMoistureLevel(); // set moisture levels
    Serial.print(jade.getMoistureLevel());
    Serial.println();
    
    jade.waterIfNeeded();
    
    delay(eightHours); // ms * sec * min * hr
}