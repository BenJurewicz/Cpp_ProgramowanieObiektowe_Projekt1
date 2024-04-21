#include <algorithm>

#include "fox.h"

Fox::Fox(Point<int> startingPoint, World *world) : Animal(3, 7, startingPoint, world) {}

char Fox::getIcon() const {
    return 'F';
}

bool Fox::isTileSafe(Point<int> point) const {
    if (world->isOccupied(point)) {
        auto creature = world->getTile(point);
        if (typeid(creature) == typeid(this)) {
            return true;
        }
        return strength >= creature->getStrength();
    }
    return true;
}

std::vector<Point<int>> Fox::getNeighbours() const {
    // removes the tiles that have a attacker with strength greater than the fox
    auto neighbours = Animal::getNeighbours();
    std::vector<Point<int>> safeNeighbours;
    std::copy_if(neighbours.begin(), neighbours.end(), std::back_inserter(safeNeighbours),
                 [this](Point<int> point) { return isTileSafe(point); });
    return safeNeighbours;
}