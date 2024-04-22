#include <chrono>
#include <thread>

#include "world.h"
#include "rng.h"
#include "creatures/animals/wolf.h"
#include "creatures/animals/sheep.h"
#include "creatures/plants/mlecz.h"
#include "creatures/plants/grass.h"
#include "creatures/plants/guarana.h"
#include "creatures/plants/wilczeJagody.h"
#include "creatures/plants/barszczSosnowskiego.h"
#include "creatures/animals/fox.h"
#include "creatures/animals/antelope.h"
#include "creatures/animals/turtle.h"
#include "creatures/animals/human.h"

void World::resizeMap() {
    map.resize(worldHeight);
    for (int i = 0; i < worldHeight; i++) {
        map[i].resize(worldWidth);
        for (int j = 0; j < worldWidth; j++) {
            map[i][j].resize(2);
            map[i][j][0].reset();
            map[i][j][1].reset();
        }
    }
}

Point<int> World::getRandomFreeCell() {
    Point<int> pos;
    std::vector<std::shared_ptr<Creature> > cell;
    do {
        pos = Point<int>::randomPoint(worldWidth - 1, worldHeight - 1);
        cell = map[pos.getY()][pos.getX()];
    } while (cell[0].get() != nullptr);
    return pos;
}

void World::addCreature(const std::shared_ptr<Creature> &creature) {
    creatures.push_back(creature);
    Point<int> pos = creature->getPosition();
    map[pos.getY()][pos.getX()][0] = creatures.back();
}

template<class S>
void World::createSpecies() {
    int speciesCount = Rng::intFromRange(minSpeciesCount, maxSpeciesCount);
    for (int i = 0; i < speciesCount; i++) {
        Point<int> pos = getRandomFreeCell();
        addCreature(std::make_shared<S>(pos, this));
    }
}

void World::createCreatures() {
    /// Human
    addCreature(std::make_shared<Human>(Point<int>(2, 2), this));
    /// Animals
    createSpecies<Wolf>();
    createSpecies<Sheep>();
    createSpecies<Fox>();
    createSpecies<Turtle>();
    createSpecies<Antelope>();
    /// Plants
    createSpecies<Mlecz>();
    createSpecies<Grass>();
    createSpecies<Guarana>();
    createSpecies<WilczeJagody>();
    createSpecies<BarszczSosnowskiego>();
}

World::World(int worldHeight, int worldWidth) : World(worldHeight, worldWidth, 1,
                                                      (int) (worldWidth * worldHeight * 0.02)) {}

World::World(int worldHeight, int worldWidth, int minSpeciesCount, int maxSpeciesCount) : worldHeight(worldHeight),
                                                                                          worldWidth(worldWidth),
                                                                                          minSpeciesCount(
                                                                                                  minSpeciesCount),
                                                                                          maxSpeciesCount(
                                                                                                  maxSpeciesCount) {
    resizeMap();
    createCreatures();
}

void World::drawMapCell(Console &console, const std::vector<std::shared_ptr<Creature>> &cell) {
    if (cell.empty() || cell[0] == nullptr) {
        console << ' ';
    } else {
        console << cell[0].get()->getIcon();
    }
}

void World::drawMap(Console &console, int y, int x) {
    console.drawBorder(y++, x++, worldHeight + 2, worldWidth + 2, "Map");
    console << clearBuffer << moveCursor(y++, x);

    for (const auto &row: map) {
        for (const auto &cell: row) {
            drawMapCell(console, cell);
        }
        console << flushBuffer << moveCursor(y++, x);
    }
}

void World::removeDeadCreatures() {
    for (const auto &creature: creatures) {
        if (!creature->getIsAlive()) {
            Point<int> pos = creature->getPosition();
            map[pos.getY()][pos.getX()][0].reset();
        }
    }
    creatures.remove_if([](const std::shared_ptr<Creature> &creature) { return !creature->getIsAlive(); });
}

void World::sortCreaturesByPriority() {
    creatures.sort([](const std::shared_ptr<Creature> &a, const std::shared_ptr<Creature> &b) {
        int ai = a->getInitiative();
        int bi = b->getInitiative();
        return ai == bi ? a->getAge() > b->getAge() : ai > bi;
    });
}

void World::doTurn() {
    removeDeadCreatures();
    sortCreaturesByPriority();
    for (const auto &creature: creatures) {
        if (creature->getIsAlive()) {
            creature->doTurn();
        }
    }
}

Point<int> World::getDimensions() const {
    return Point<int>(worldWidth, worldHeight);
}

std::shared_ptr<Creature> World::getTile(Point<int> position) {
    return map[position.getY()][position.getX()][0];
}

bool World::isOccupied(Point<int> point) {
    return map.at(point.getY()).at(point.getX()).at(0).get() != nullptr;
}

void World::startLoopNoInput(Console &console, int turns) {
    console << clearBuffer;
    console.refreshWindow();
    drawMap(console, 1, 1);
    Log::getInstance()->draw(worldHeight + 4, 1, console.getWidth() - 2);
    for (int i = 0; i < turns; i++) {
        console << moveCursor(0, 1) << "Benjamin Jurewicz s198326" << flushBuffer;
        doTurn();
        drawMap(console, 1, 1);
        Log::getInstance()->draw(worldHeight + 4, 1, console.getWidth() - 2);
//        console << moveCursor(1, 1) << "Creature count: " << creatures.size()
//                << flushBuffer;
        console.refreshWindow();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void World::moveCreature(const std::shared_ptr<Creature> &creature, Point<int> point) {
    Point<int> pos = creature->getPosition();
    map[pos.y()][pos.x()][0].reset();
    map[point.y()][point.x()][0] = creature;

    creature->setPosition(point);
}

int World::getHeight() const {
    return worldHeight;
}

[[maybe_unused]] int World::getWidth() const {
    return worldWidth;
}

//void World::save() {
//    std::ofstream stream("save.txt");
//    for(auto creature: creatures) {
//        creature->serialize();
//    }
//}

