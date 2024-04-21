#ifndef PROJEKT1CPP_ANIMAL_H
#define PROJEKT1CPP_ANIMAL_H

#include "../creature.h"

class World;

class Animal : public Creature {
protected:
    Animal(int strength, int initiative, Point<int> position, World *world);

    /**
     * Move the animal to a random position and handle possible collision
     * @param correctNewPosition the position to move to, make sure it is correct as there is no checking
     */
    virtual void move(Point<int> correctNewPosition);

    virtual void tryMating(Creature *creature);

public:

    void doTurn() override;

    void collide(Creature *creature) override;
};


#endif //PROJEKT1CPP_ANIMAL_H
