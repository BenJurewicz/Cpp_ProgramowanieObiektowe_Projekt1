#ifndef PROJEKT1CPP_SHEEP_H
#define PROJEKT1CPP_SHEEP_H

#include "animal.h"

class Sheep : public Animal {
public:
    Sheep(Point<int> startingPosition, World *world);

    [[nodiscard]] char getIcon() const override;
};


#endif //PROJEKT1CPP_SHEEP_H
