#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>

typedef struct {
    char* name;
    int moistureLevel;
    int drynessLimit;
} Plant;

bool waterIfNeeded(Plant plant) {
    if (plant.moistureLevel > plant.drynessLimit) {
        return true;
    } else {
        return false;
    }
}