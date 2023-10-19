#include "plant.h"

Plant jade(A0, 2, 480); // plant object
String truth("true");

void setup() {
    Serial.begin(115200);
    jade.setOutput(jade.getOutput());
    digitalWrite(jade.getOutput(), HIGH);
    jade.setInput(jade.getInput());
}

void loop() {
  if (Serial.available() > 0) {
    String activator = Serial.readString();
    if (activator == truth)  {
      jade.setMoistureLevel();
      Serial.println(jade.getMoistureLevel());
      jade.waterIfNeeded();
    }
  }
}