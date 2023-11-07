#include <stdio.h>
#include <termios.h>

typedef struct {
    char* name;
    int moistureLevel;
    int drynessLimit;
} Plant;

void waterIfNeeded(Plant plant) {
    if (plant.moistureLevel > plant.drynessLimit) {

    }
}