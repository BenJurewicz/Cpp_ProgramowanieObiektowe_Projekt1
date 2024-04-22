#include "mlecz.h"

Mlecz::Mlecz(Point<int> startingPoint, World *world) : Plant(0, startingPoint, world) {}

char Mlecz::getIcon() const {
    return 'm';
}

void Mlecz::clone(Point<int> pos) {
    world->addCreature(std::make_shared<Mlecz>(pos, world));
}

void Mlecz::doTurn() {
    trySpreading();
    trySpreading();
    Plant::doTurn();
}
