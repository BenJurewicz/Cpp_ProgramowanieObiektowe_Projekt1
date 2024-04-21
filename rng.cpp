#include "rng.h"

bool Rng::initialized = false;

void Rng::init() {
    if (initialized) {
        return;
    }
    srand(time(NULL));
    initialized = true;
}

int Rng::intFromRange(int includedMin, int includedMax) {
    if (!initialized) {
        init();
    }
    return (rand() % (includedMax - includedMin + 1) + includedMin);
}