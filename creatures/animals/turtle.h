#ifndef PROJEKT1CPP_TURTLE_H
#define PROJEKT1CPP_TURTLE_H

#include "animal.h"

class Turtle : public Animal {
public:
    Turtle(Point<int> startingPoint, World *world);

    char getIcon() const override;

    bool didDeflectAttack(Creature *creature) override;

protected:
    void move(Point<int> correctNewPosition) override;

    void clone(Point<int> pos) override;
};


#endif //PROJEKT1CPP_TURTLE_H
