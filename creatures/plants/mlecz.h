#ifndef PROJEKT1CPP_MLECZ_H
#define PROJEKT1CPP_MLECZ_H

#include "plant.h"

// The English name is wierd so Polish it is
class Mlecz : public Plant {
public:
    Mlecz(Point<int> startingPoint, World *world);

    char getIcon() const override;

    void clone(Point<int> pos) override;

    void doTurn() override;
};


#endif //PROJEKT1CPP_MLECZ_H
