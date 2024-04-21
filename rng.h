#ifndef PROJEKT1CPP_RNG_H
#define PROJEKT1CPP_RNG_H

#include <ctime>
#include <cstdlib>

class Rng {
    static bool initialized;
public:
    static void init();

    static int intFromRange(int includedMin, int includedMax);
};

#endif //PROJEKT1CPP_RNG_H
