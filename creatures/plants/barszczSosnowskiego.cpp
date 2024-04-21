#include "barszczSosnowskiego.h"
#include "../animals/animal.h"

BarszczSosnowskiego::BarszczSosnowskiego(Point<int> position, World *world) : Plant(10, position, world) {}

void BarszczSosnowskiego::handleCollision(Creature *collider) {
    Log &log = *Log::getInstance();
    log.add(toString() + " was ate by and killed " + collider->toString());
    collider->kill();
    this->kill();
}

char BarszczSosnowskiego::getIcon() const {
    return 'b';
}

void BarszczSosnowskiego::doTurn() {
    age++;
    Log &log = *Log::getInstance();
    for (auto &tile: getNeighbours()) {
        if (world->isOccupied(tile)) {
            std::shared_ptr<Creature> creature = world->getTile(tile);
            if (auto *animal = dynamic_cast<Animal *>(creature.get())) {
                log.add(toString() + " poisoned by air and killed " + animal->toString());
            }
        }
    }
}
