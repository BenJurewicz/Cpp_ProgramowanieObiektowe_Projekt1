#include "animal.h"

Animal::Animal(int strength, int initiative, Point<int> position, World *world) : Creature(strength, initiative,
                                                                                           position, world) {}

void Animal::move(Point<int> correctNewPosition) {
    Log &log = *Log::getInstance();
    if (correctNewPosition == Point<int>(-1, -1)) {
        log.add("No space to move for a animal " + toString() + " to move");
        return;
    }
    if (world->isOccupied(correctNewPosition)) {
        collide(world->getTile(correctNewPosition).get());
        if (world->isOccupied(correctNewPosition)) {
            /**
             * We check again so that
             * if we killed the creature, or it ran away we move there
             * but if we got killed or the creature deflected, or we mated we don't move there
             */
            return;
        }
    }
//    log.add(toString() + " moved to " + correctNewPosition.toString());
    world->moveCreature(shared_from_this(), correctNewPosition);
}

void Animal::doTurn() {
    age++;
    move(getRandomCorrectNeighbour(false));
}

void Animal::collide(Creature *creature) {
    if (typeid(*this) == typeid(*creature)) {
        tryMating(creature);
//        Log::getInstance()->add(toString() + " tried mating with " + creature->toString());
    } else {
        Creature::collide(creature);
    }
}

void Animal::tryMating(Creature *creature) {
    // TODO implement
}
