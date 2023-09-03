#include "plant.h"

// constructor & destructor
Plant::Plant() {}
Plant::Plant(const Plant &source) {}
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
