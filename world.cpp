#include <chrono>
#include <thread>

#include "world.h"
#include "rng.h"
#include "creatures/animals/wolf.h"
#include "creatures/animals/sheep.h"

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

template<class S>
void World::createSpecies(int minSpeciesCount, int maxSpeciesCount) {
    int speciesCount = Rng::intFromRange(minSpeciesCount, maxSpeciesCount);
    for (int i = 0; i < speciesCount; i++) {
        Point<int> pos = getRandomFreeCell();
        creatures.push_back(std::make_shared<S>(pos, this));
        map[pos.getY()][pos.getX()][0] = creatures.back();
    }
}

void World::createCreatures() {
    int maxSpeciesCount = 5;
    int minSpeciesCount = 2;
    createSpecies<Wolf>(minSpeciesCount, maxSpeciesCount);
    createSpecies<Sheep>(minSpeciesCount, maxSpeciesCount);

}

World::World(int worldHeight, int worldWidth) : worldHeight(worldHeight), worldWidth(worldWidth) {
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
    console.drawBorder(y++, x++, worldHeight + 2, worldWidth + 2);
    console << clearBuffer << moveCursor(y++, x);

    for (const auto &row: map) {
        for (const auto &cell: row) {
            drawMapCell(console, cell);
        }
        console << flushBuffer << moveCursor(y++, x);
    }
}

void World::doTurn() {
    auto compare = [](const std::shared_ptr<Creature> &a, const std::shared_ptr<Creature> &b) {
        int ai = a->getInitiative();
        int bi = b->getInitiative();
        return ai == bi ? a->getAge() > b->getAge() : ai > bi;
    };
    creatures.sort(compare);
    for (const auto &creature: creatures) {
        creature->doTurn();
    }
}

Point<int> World::getDimensions() const {
    return Point<int>(worldWidth, worldHeight);
}

std::shared_ptr<Creature> World::getTile(Point<int> position) {
    return map[position.getY()][position.getX()][0];
}

std::function<Console &(Console &)> World::moveCursorToLogPoint() const {
    return moveCursor(worldHeight + 3, 1);
}

bool World::isOccupied(Point<int> point) {
    return map.at(point.getY()).at(point.getX()).at(0).get() != nullptr;
}

[[maybe_unused]] void World::startLoopNoInput(Console &console, int turns) {
    console << clearBuffer;
    drawMap(console, 1, 1);
    console.refreshWindow();
    for (int i = 0; i < turns; i++) {
        doTurn();
        drawMap(console, 1, 1);
        Log::getInstance()->draw(worldHeight + 3, 0);
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

void World::clearLog(Console &console) const {
    console.drawHorizontalLine(worldHeight + 3, 0, console.getWidth(), ' ');
}

