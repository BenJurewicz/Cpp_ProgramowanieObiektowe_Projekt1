#include "animal.h"
#include "wolf.h"
#include "sheep.h"
#include "turtle.h"
#include "antelope.h"
#include "fox.h"

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
        Log::getInstance()->add(toString() + " tried mating with " + creature->toString());
    } else {
        Creature::collide(creature);
    }
}

void Animal::tryMating(Creature *creature) {
    if (Rng::intFromRange(0, 3) == 0) {
        return;
    }
    Point<int> candide = getRandomCorrectNeighbour(true);
    if (candide != Point<int>(-1, -1)) {
        clone(candide);
    }
}

void Animal::serialize(std::ofstream &stream) {
    stream << "Z " << getIcon() << " " << position.x() << " " << position.y() << " " << getAge() << " " << strength
           << std::endl;
}

std::shared_ptr<Animal> Animal::deserialize(std::ifstream &stream, World *world) {
    std::shared_ptr<Animal> ptr;
    std::string animalType;
    stream >> animalType;

    int x, y;
    stream >> x >> y;
    int age;
    stream >> age;
    int str;
    stream >> str;

    if (animalType == "W") {
        ptr = std::make_shared<Wolf>(Point<int>(x, y), world);
    } else if (animalType == "S") {
        ptr = std::make_shared<Sheep>(Point<int>(x, y), world);
    } else if (animalType == "F") {
        ptr = std::make_shared<Fox>(Point<int>(x, y), world);
    } else if (animalType == "T") {
        ptr = std::make_shared<Turtle>(Point<int>(x, y), world);
    } else if (animalType == "A") {
        ptr = std::make_shared<Antelope>(Point<int>(x, y), world);
    } else {
        throw std::runtime_error("Unknown animal type: " + animalType);
    }
    ptr->setAge(age);
    ptr->setStrength(str);
    return ptr;
}
