#include "wolf.h"

Wolf::Wolf(Point<int> startingPos, World *world) : Animal(9, 5, startingPos,
                                                          world) {}

char Wolf::getIcon() const {
    return 'W';
}

void Wolf::collision() {

}