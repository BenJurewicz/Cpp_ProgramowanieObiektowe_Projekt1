#include <memory>

#include "plant.h"

Plant::Plant(int strength, Point<int> position, World *world) : Creature(strength, 0, position, world) {}

void Plant::trySpreading() const {
    if (Rng::intFromRange(0, 4) > 1) {
        return;
    }
    Point<int> newPosition = getRandomCorrectNeighbour(true);
    Log &log = *Log::getInstance();
    if (world->isOccupied(newPosition) || newPosition == Point<int>(-1, -1)) {
        log.add("No space to spread for a plant " + toString());
        return;
    } else {
        log.add("Plant " + toString() + " spread to " + newPosition.toString());
        // TODO implement
    }
}

void Plant::doTurn() {
//    trySpreading();
age++;
}