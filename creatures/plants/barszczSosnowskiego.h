#ifndef PROJEKT1CPP_BARSZCZSOSNOWSKIEGO_H
#define PROJEKT1CPP_BARSZCZSOSNOWSKIEGO_H

#include "plant.h"

class BarszczSosnowskiego : public Plant {

public:
    BarszczSosnowskiego(Point<int> position, World *world);

    void handleCollision(Creature *collider) override;

    void doTurn() override;

    char getIcon() const override;

    void clone(Point<int> pos) override;
};


#endif //PROJEKT1CPP_BARSZCZSOSNOWSKIEGO_H
