#ifndef plant_h
#define plant_h

#include "Arduino.h"

class Plant {
public:
    // constructor & destructor
    Plant(int ip, int op, int dl);
    Plant(const Plant &source);
    ~Plant();

    // getters & setters
    int getInput();
    int getOutput();
    int getMoistureLevel();
    int getDrynessLimit();

    void setInput(int in);
    void setOutput(int in);
    void setMoistureLevel();
    void setDrynessLimit(int in);

    // methods
    void waterIfNeeded();

private:
    int inputPin;
    int outputPin;
    int moistureLevel;
    int drynessLimit; // maybe change for an enum once dryness numbers are better understood
};

#endif