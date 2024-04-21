#include "mlecz.h"

Mlecz::Mlecz(Point<int> startingPoint, World *world) : Plant(0, startingPoint, world) {}

char Mlecz::getIcon() const {
    return 'm';
}
