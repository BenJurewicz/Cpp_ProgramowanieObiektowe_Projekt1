//
// Created by essa on 22.04.2024.
//

#include "turtle.h"

Turtle::Turtle(Point<int> startingPoint, World *world) : Animal(2, 1, startingPoint, world) {}

char Turtle::getIcon() const {
    return 'T';
}

bool Turtle::didDeflectAttack(Creature *creature) {
    if (creature->getStrength() < 5) {
        Log::getInstance()->add(toString() + " deflected attack from " + creature->toString());
        return true;
    }
    return false;
}

void Turtle::move(Point<int> correctNewPosition) {
    if (Rng::intFromRange(0, 3) == 0) {
        Animal::move(correctNewPosition);
    }
}

void Turtle::clone(Point<int> pos) {
    world->addCreature(std::make_shared<Turtle>(pos, world));
}

