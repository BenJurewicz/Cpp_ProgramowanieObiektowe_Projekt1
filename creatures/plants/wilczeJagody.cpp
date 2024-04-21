#include "wilczeJagody.h"

WilczeJagody::WilczeJagody(Point<int> position, World *world) : Plant(99, position, world) {}

void WilczeJagody::handleCollision(Creature *collider) {
    Log &log = *Log::getInstance();
    log.add(toString() + " killed " + collider->toString());
    collider->kill();
    this->kill();
}

char WilczeJagody::getIcon() const {
    return 'w';
}
