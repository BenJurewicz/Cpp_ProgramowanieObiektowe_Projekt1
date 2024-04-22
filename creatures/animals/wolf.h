#ifndef PROJEKT1CPP_WOLF_H
#define PROJEKT1CPP_WOLF_H

#include "animal.h"

class Wolf : public Animal {
public:
    Wolf(Point<int> startingPosition, World *world);

    [[nodiscard]] char getIcon() const override;

    void clone(Point<int> pos) override;
};


#endif //PROJEKT1CPP_WOLF_H
