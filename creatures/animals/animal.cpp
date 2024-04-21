#include "animal.h"

Animal::Animal(int strength, int initiative, Point<int> position, World *world) : Creature(strength, initiative,
                                                                                           position, world) {}

void Animal::move() {
    Point<int> newPosition = getRandomCorrectNeighbour(false);
    Console &c = *Console::getInstance();
    world->clearLog(c);
    c << world->moveCursorToLogPoint();
    if (newPosition == Point<int>(-1, -1)) {
        c << "No space to move for a animal " << static_cast<Creature &>(*this) << flushBuffer;
        return;
    }
    if (world->isOccupied(newPosition)) {
        c << "Collision between animals " << static_cast<Creature &>(*this) << flushBuffer;
        return;
    }
//    c << "Animal " << static_cast<Creature &>(*this) << " moved to " << newPosition
//      << flushBuffer;

    Log::getInstance()->add(
            "Animal " + static_cast<Creature &>(*this).toString() + " moved to " + newPosition.toString() + "\n");
    world->moveCreature(shared_from_this(), newPosition);
}

void Animal::doTurn() {
    age++;
    move();
}
