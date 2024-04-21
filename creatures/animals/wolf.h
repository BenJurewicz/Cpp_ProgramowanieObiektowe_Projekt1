#ifndef PROJEKT1CPP_WOLF_H
#define PROJEKT1CPP_WOLF_H

#include "animal.h"

class Wolf : public Animal {
public:
    Wolf(Point<int> startingPosition, World *world);

    void collision() override;

    [[nodiscard]] char getIcon() const override;
};


#endif //PROJEKT1CPP_WOLF_H
