#ifndef PROJEKT1CPP_ANIMAL_H
#define PROJEKT1CPP_ANIMAL_H

//#include "../creature.h"
#include "../creature.h"

class World;

class Animal : public Creature {
protected:
    Animal(int strength, int initiative, Point<int> position, World *world);

    virtual void move();

    virtual void tryMating(Creature *creature);

public:

    void doTurn() override;

    void collide(Creature *creature) override;
};


#endif //PROJEKT1CPP_ANIMAL_H
