#include "animal.h"

Animal::Animal(int strength, int initiative, Point<int> position, World *world) : Creature(strength, initiative,
                                                                                           position, world) {}

void Animal::move() {
    Point<int> newPosition = getRandomCorrectNeighbour(false);
    Console &c = *Console::getInstance();
    Log &log = *Log::getInstance();
    if (newPosition == Point<int>(-1, -1)) {
        log.add("No space to move for a animal " + toString());
        return;
    }
    if (world->isOccupied(newPosition)) {
        collide(world->getTile(newPosition).get());
        return;
    }
//    log.add("Animal moved to " + newPosition.toString());
    world->moveCreature(shared_from_this(), newPosition);
}

void Animal::doTurn() {
    age++;
    move();
}

void Animal::collide(Creature *creature) {
    if (typeid(*this) == typeid(*creature)) {
        tryMating(creature);
        Log::getInstance()->add(toString() + " tried mating with " + creature->toString());
    } else {
        Creature::collide(creature);
    }
}

void Animal::tryMating(Creature *creature) {
    // TODO implement
}
