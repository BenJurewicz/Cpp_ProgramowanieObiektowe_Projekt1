#ifndef PROJEKT1CPP_WILCZEJAGODY_H
#define PROJEKT1CPP_WILCZEJAGODY_H

#include "plant.h"

class WilczeJagody : public Plant {
public:
    WilczeJagody(Point<int> position, World *world);

    void handleCollision(Creature *collider) override;

    char getIcon() const override;

    void clone(Point<int> pos) override;
};


#endif //PROJEKT1CPP_WILCZEJAGODY_H
