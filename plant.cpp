#include "plant.h"

// constructor & destructor
Plant::Plant(int ip, int op, int dl)
    :inputPin{ip}, outputPin{op}, drynessLimit{dl} {
        moistureLevel = 0;
    }
Plant::Plant(const Plant &source)
    :inputPin{source.inputPin}, outputPin{source.outputPin}, moistureLevel{source.moistureLevel}, drynessLimit{source.drynessLimit} {}
Plant::~Plant() {}

// getters & setters
int Plant::getInput() {
    return inputPin;
}
int Plant::getOutput() {
    return outputPin;
}
int Plant::getMoistureLevel() {
    return moistureLevel;
}
int Plant::getDrynessLimit() {
    return drynessLimit;
}

void Plant::setInput(int in) {
    pinMode(in, INPUT);
}
void Plant::setOutput(int in) {
    pinMode(in, OUTPUT);
}
void Plant::setMoistureLevel() {
    moistureLevel = analogRead(this->inputPin);
}
void Plant::setDrynessLimit(int in) {
    drynessLimit = in;
}

//methods
void Plant::waterIfNeeded() {
    unsigned long startMillis = millis();
    if (this->getMoistureLevel() > this->getDrynessLimit()) { // while moisture levels are below desired level
        Serial.print("Starting watering");
        digitalWrite(this->getOutput(), LOW); // start pump
        delay(5000);
        // while (millis() - startMillis < 1000 * 60 * 5); // ms * sec * min
        digitalWrite(this->getOutput(), HIGH); //stop pump
        Serial.print("Stopped watering");
    }
}
