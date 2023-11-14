#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>

typedef struct {
    char* name;
    long moistureLevel;
    long drynessLimit;
} Plant;

bool waterIfNeeded(Plant plant) {
    if (plant.moistureLevel > plant.drynessLimit) {
        return true;
    } else {
        return false;
    }
}