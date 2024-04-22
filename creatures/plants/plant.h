#ifndef PROJEKT1CPP_PLANT_H
#define PROJEKT1CPP_PLANT_H

#include "../creature.h"

class Plant : public Creature {
protected:
    Plant(int strength, Point<int> position, World *world);

    virtual void trySpreading();

public:

    void doTurn() override;

    static std::shared_ptr<Plant> deserialize(std::ifstream &stream, World *world);

    void serialize(std::ofstream &stream) override;
};


#endif //PROJEKT1CPP_PLANT_H
