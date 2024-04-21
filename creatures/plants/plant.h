#ifndef PROJEKT1CPP_PLANT_H
#define PROJEKT1CPP_PLANT_H

#include "../creature.h"

class Plant : public Creature {
protected:
    Plant(int strength, Point<int> position, World *world);

    virtual void trySpreading() const;

public:

    void doTurn() override;
};


#endif //PROJEKT1CPP_PLANT_H
