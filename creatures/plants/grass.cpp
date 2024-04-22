#include "grass.h"

Grass::Grass(Point<int> startingPoint, World *world) : Plant(0, startingPoint, world) {}

char Grass::getIcon() const {
    return 'g';
}

void Grass::clone(Point<int> pos) {
    world->addCreature(std::make_shared<Grass>(pos, world));
}
