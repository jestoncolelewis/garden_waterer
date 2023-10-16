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
    if (this->getMoistureLevel() > this->getDrynessLimit()) { // if moisture levels are below desired level
        Serial.print("Starting watering\n");
        Serial.print(this->getOutput());
        digitalWrite(this->getOutput(), LOW); // start pump
        delay(5000); // 5 seconds
        digitalWrite(this->getOutput(), HIGH); // stop pump
        Serial.print("Stopped watering\n");
    }
}
