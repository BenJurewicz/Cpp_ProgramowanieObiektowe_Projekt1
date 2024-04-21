#include "guarana.h"

Guarana::Guarana(Point<int> startingPoint, World *world) : Plant(0, startingPoint, world) {}

char Guarana::getIcon() const {
    return 'u';
}

void Guarana::handleCollision(Creature *collider) {
    Log::getInstance()->add(collider->toString() + " ate guarana and gained 3 strength (new strength: " +
                            std::to_string(collider->getStrength() + 3) + ")");
    collider->setStrength(collider->getStrength() + 3);
}
