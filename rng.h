#ifndef PROJEKT1CPP_RNG_H
#define PROJEKT1CPP_RNG_H

#include <algorithm>
#include <random>

class Rng {
    static bool initialized;
    static std::mt19937 generator;
public:
    static void init();

    static int intFromRange(int includedMin, int includedMax);

    static std::mt19937 &getGenerator();
};

#endif //PROJEKT1CPP_RNG_H
