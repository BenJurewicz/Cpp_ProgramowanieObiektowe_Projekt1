#ifndef PROJEKT1CPP_ANTELOPE_H
#define PROJEKT1CPP_ANTELOPE_H

#include <vector>

#include "animal.h"

class Antelope : public Animal {
protected:
    std::vector<Point<int>> getNeighbours() const override;

public:
    Antelope(Point<int> position, World *world);

    char getIcon() const override;

    bool tryRunningAway(Creature *creature) override;
};


#endif //PROJEKT1CPP_ANTELOPE_H
