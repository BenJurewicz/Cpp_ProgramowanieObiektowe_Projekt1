#include "antelope.h"

Antelope::Antelope(Point<int> position, World *world) : Animal(4, 4, position, world) {}

char Antelope::getIcon() const {
    return 'A';
}

bool Antelope::tryRunningAway(Creature *creature) {
    Log &log = *Log::getInstance();
    bool shouldRunAway = Rng::intFromRange(0, 1) == 1;
    Point<int> newPosition = getRandomCorrectNeighbour(true);
    if (shouldRunAway && newPosition != Point<int>(-1, -1)) {
        move(newPosition);
        log.add(toString() + " ran away from " + creature->toString());
    } else {
        log.add(toString() + " tried running away and failed " + creature->toString());
    }
    return shouldRunAway;
}

std::vector<Point<int>> Antelope::getNeighbours() const {
    auto neighbours = Creature::getNeighbours();
    auto newNeighbours = neighbours;
    Point<int> neighbourCandidate;
    Point<int> direction;

    // adds the tiles that are two tiles away from the antelope
    for (auto neighbour: neighbours) {
        direction = neighbour - position;
        neighbourCandidate = neighbour + direction;
        if (neighbourCandidate.between(Point<int>::ZERO, world->getDimensions() - 1)) {
            newNeighbours.push_back(neighbourCandidate);
        }
    }

    return newNeighbours;
}

void Antelope::clone(Point<int> pos) {
    world->addCreature(std::make_shared<Antelope>(pos, world));
}
