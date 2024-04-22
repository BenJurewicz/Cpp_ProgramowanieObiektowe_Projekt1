#include <memory>

#include "plant.h"
#include "mlecz.h"
#include "guarana.h"
#include "grass.h"
#include "barszczSosnowskiego.h"

Plant::Plant(int strength, Point<int> position, World *world) : Creature(strength, 0, position, world) {}

void Plant::trySpreading() {
    if (Rng::intFromRange(0, 25) > 1) {
        return;
    }
    Point<int> newPosition = getRandomCorrectNeighbour(true);
    Log &log = *Log::getInstance();
    if (newPosition != Point<int>(-1, -1) && !world->isOccupied(newPosition)) {
        log.add("Plant " + toString() + " spread to " + newPosition.toString());
        clone(newPosition);
    } else {
        log.add("No space to spread for a plant " + toString());
        return;
    }
}

void Plant::doTurn() {
    trySpreading();
    age++;
}

void Plant::serialize(std::ofstream &stream) {
    stream << "R " << getIcon() << " " << position.x() << " " << position.y() << " " << age
           << std::endl;
}

std::shared_ptr<Plant> Plant::deserialize(std::ifstream &stream, World *world) {
    std::shared_ptr<Plant> ptr;
    std::string plantType;
    stream >> plantType;

    int x, y;
    stream >> x >> y;
    int age;
    stream >> age;

    if (plantType == "m") {
        ptr = std::make_shared<Mlecz>(Point<int>(x, y), world);
    } else if (plantType == "u") {
        ptr = std::make_shared<Guarana>(Point<int>(x, y), world);
    } else if (plantType == "g") {
        ptr = std::make_shared<Grass>(Point<int>(x, y), world);
    } else if (plantType == "b") {
        ptr = std::make_shared<BarszczSosnowskiego>(Point<int>(x, y), world);
    } else {
        throw std::runtime_error("Unknown plant type: " + plantType);
    }
    ptr->setAge(age);
    return ptr;
}
