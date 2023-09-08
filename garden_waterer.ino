#include "plant.h"

unsigned long previousMillis = 0;
const long interval = 3600000; // 1 hour

Plant jade(A0, 2, 480); // plant object

void setup() {
    Serial.begin(9600);
    jade.setOutput(jade.getOutput());
    digitalWrite(jade.getOutput(), HIGH);
    jade.setInput(jade.getInput());
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)  {
    previousMillis = currentMillis;

    jade.setMoistureLevel(); // set moisture levels
    Serial.print(jade.getMoistureLevel());
    Serial.println();
  
    jade.waterIfNeeded();
  }
}