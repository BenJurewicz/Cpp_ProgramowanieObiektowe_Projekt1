#include "creature.h"

Creature::Creature(int strength, int initiative, Point<int> position, World *world) : strength(strength),
                                                                                      initiative(initiative),
                                                                                      position(position), world(world),
                                                                                      age(0),
                                                                                      isAlive(true) {}

Point<int> Creature::getRandomCorrectNeighbour(bool squareMustBeFree) {
//    Point<int> neighbours[4] = {Point<int>(1, 0), Point<int>(-1, 0), Point<int>(0, 1), Point<int>(0, -1)};
    Point<int> neighbours[4] = {Point<int>::UP, Point<int>::RIGHT, Point<int>::DOWN, Point<int>::LEFT};

    Point<int> newPos;
    int neighbourId = Rng::intFromRange(0, 3);
    int tries = 1;
    while (true) {
        newPos = position + neighbours[neighbourId];
        if (Point<int>::ZERO > newPos || newPos > (world->getDimensions() - Point<int>(1, 1))) {
            neighbourId = (neighbourId + 1) % 4;
            tries++;
            if (tries > 4) {
                return Point<int>(-1, -1);
            }
        } else {
            break;
        }
    }

    return newPos;
}

int Creature::getStrength() const {
    return strength;
}

int Creature::getInitiative() const {
    return initiative;
}

int Creature::getAge() const {
    return age;
}

Point<int> Creature::getPosition() {
    return position;
}

void Creature::setPosition(Point<int> point) {
    position = point;
}

std::string Creature::toString() const {
    std::stringstream ss;
    ss << getIcon() << ": " << position.toString();
//    ss << " Age: " << age;
    return ss.str();
}

bool Creature::didDeflectAttack(Creature *creature) {
    return false;
}

void Creature::collide(Creature *creature) {
    if (creature->didDeflectAttack(creature)) {
        return;
    }
    Log &log = *Log::getInstance();
    if (strength >= creature->getStrength()) {
        log.add(toString() + " attacked and killed " + creature->toString());
        creature->isAlive = false;
    } else {
        log.add(toString() + " attacked and was killed by " + creature->toString());
        isAlive = false;
    }
}

bool Creature::getIsAlive() const {
    return isAlive;
}

Console &operator<<(Console &console, const Creature &creature) {
    console << creature.toString();
    return console;
}
