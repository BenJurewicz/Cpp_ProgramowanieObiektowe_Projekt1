#ifndef PROJEKT1CPP_GRASS_H
#define PROJEKT1CPP_GRASS_H

#include "plant.h"

class Grass : public Plant {
public:
    Grass(Point<int> startingPoint, World *world);

    char getIcon() const override;

    void clone(Point<int> pos) override;
};


#endif //PROJEKT1CPP_GRASS_H
