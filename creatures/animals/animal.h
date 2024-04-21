#ifndef PROJEKT1CPP_ANIMAL_H
#define PROJEKT1CPP_ANIMAL_H

//#include "../creature.h"
#include "../creature.h"

class World;

class Animal : public Creature {
protected:
    Animal(int strength, int initiative, Point<int> position, World *world);

public:
    virtual void move();

    void doTurn() override;
//    void collision();
//    char getIcon();
};


#endif //PROJEKT1CPP_ANIMAL_H
