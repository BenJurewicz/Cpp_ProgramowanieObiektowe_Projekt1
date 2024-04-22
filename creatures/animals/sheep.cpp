//
// Created by essa on 18.04.2024.
//

#include "sheep.h"

Sheep::Sheep(Point<int> startingPosition, World *world) : Animal(4, 4, startingPosition, world) {}

char Sheep::getIcon() const {
    return 'S';
}

void Sheep::clone(Point<int> pos) {
    world->addCreature(std::make_shared<Sheep>(pos, world));
}
