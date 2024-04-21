#include "creature.h"

Creature::Creature(int strength, int initiative, Point<int> position, World *world) : strength(strength),
                                                                                      initiative(initiative),
                                                                                      position(position), world(world),
                                                                                      age(0),
                                                                                      isAlive(true) {}

Point<int> Creature::getRandomCorrectNeighbour(bool squareMustBeFree) const {
    std::vector<Point<int>> neighbours = getNeighbours();
    std::shuffle(neighbours.begin(), neighbours.end(), Rng::getGenerator());

    if (neighbours.empty()) {
        return Point<int>(-1, -1);
    }
    if (!squareMustBeFree) {
        return neighbours.at(0);
    }

    for (auto &neighbour: neighbours) {
        if (!world->isOccupied(neighbour)) {
            return neighbour;
        }
    }
    return Point<int>(-1, -1);
}

std::vector<Point<int>> Creature::getNeighbours() const {
    const Point<int> worldDimensions = world->getDimensions();
    std::vector<Point<int>> neighbours;
    Point<int> newPos;

    for (Point<int> direction: Point<int>::cardinalDirections) {
        newPos = position + direction;
        if (newPos.between(Point<int>::ZERO, worldDimensions - 1)) {
            neighbours.push_back(newPos);
        }
    }
    return neighbours;
};

int Creature::getStrength() const {
    return strength;
}

void Creature::setStrength(int newStrength) {
    strength = newStrength;
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
    ss << " Age: " << age;
    ss << " Str: " << strength;
    return ss.str();
}

bool Creature::didDeflectAttack(Creature *creature) {
    return false;
}

void Creature::collide(Creature *creature) {
    if (creature->didDeflectAttack(this)) {
        return;
    }
    if (creature->tryRunningAway(this)) {
        return;
    }
    creature->handleCollision(this);
    if (!isAlive) {
        // in case we kill the creature in handleCollision
        return;
    }
    fight(creature);
}

void Creature::fight(Creature *creature) {
    Log &log = *Log::getInstance();
    if (strength >= creature->getStrength()) {
        log.add(toString() + " attacked and killed " + creature->toString());
        creature->kill();
    } else {
        log.add(toString() + " attacked and was killed by " + creature->toString());
        kill();
    }
}

bool Creature::getIsAlive() const {
    return isAlive;
}

void Creature::handleCollision(Creature *collider) {}

void Creature::kill() {
    isAlive = false;
}

bool Creature::tryRunningAway(Creature *creature) {
    return false;
}


Console &operator<<(Console &console, const Creature &creature) {
    console << creature.toString();
    return console;
}
