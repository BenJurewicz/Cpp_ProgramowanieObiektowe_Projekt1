#ifndef PROJEKT1CPP_FOX_H
#define PROJEKT1CPP_FOX_H

#include <vector>

#include "animal.h"

class Fox : public Animal {
    bool isTileSafe(Point<int> point) const;

protected:
    std::vector<Point<int>> getNeighbours() const override;

public:
    Fox(Point<int> startingPoint, World *world);

    char getIcon() const override;

    void clone(Point<int> pos) override;
};


#endif //PROJEKT1CPP_FOX_H
