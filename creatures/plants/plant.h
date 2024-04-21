#ifndef PROJEKT1CPP_PLANT_H
#define PROJEKT1CPP_PLANT_H

#include "../creature.h"

class Plant : public Creature {
protected:
    Plant(int strength, Point<int> position, World *world);

public:

//    void doTurn();
//    void collide();
//    char getIcon();
};


#endif //PROJEKT1CPP_PLANT_H
