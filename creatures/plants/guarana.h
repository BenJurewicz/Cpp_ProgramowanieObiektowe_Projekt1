#ifndef PROJEKT1CPP_GUARANA_H
#define PROJEKT1CPP_GUARANA_H

#include "plant.h"

class Guarana : public Plant {
public:
    Guarana(Point<int> startingPoint, World *world);

    char getIcon() const override;

    void handleCollision(Creature *collider) override;

    void clone(Point<int> pos) override;
};


#endif //PROJEKT1CPP_GUARANA_H
