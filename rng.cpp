#include "rng.h"

bool Rng::initialized = false;
std::mt19937 Rng::generator;

void Rng::init() {
    if (initialized) {
        return;
    }
    generator = std::mt19937(std::random_device()());

    initialized = true;
}

int Rng::intFromRange(int includedMin, int includedMax) {
    if (!initialized) {
        init();
    }
    std::uniform_int_distribution<int> distribution(includedMin, includedMax);
    return distribution(generator);
}

std::mt19937 &Rng::getGenerator() {
    return generator;
}
