#ifndef PROJEKT1CPP_HUMAN_H
#define PROJEKT1CPP_HUMAN_H

#include "animal.h"

class Human : public Animal {
    int abilityStrength;
    int abilityCooldown;

    Point<int> getMoveFromUser();

    void handleAbilityActivation();

    Point<int> translateDirectionToNewPosition(Point<int> direction) const;

public:
    Human(Point<int> startingPoint, World *world);

    char getIcon() const override;

    int getStrength() const override;

    void doTurn() override;

    void activateAbility();
};


#endif //PROJEKT1CPP_HUMAN_H
