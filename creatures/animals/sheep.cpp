//
// Created by essa on 18.04.2024.
//

#include "sheep.h"

Sheep::Sheep(Point<int> startingPosition, World *world) : Animal(4, 4, startingPosition, world) {}

void Sheep::collision() {

}

char Sheep::getIcon() const {
    return 'S';
}

