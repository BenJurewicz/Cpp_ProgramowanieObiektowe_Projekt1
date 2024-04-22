#include "human.h"
#include <ncurses.h>

Human::Human(Point<int> startingPoint, World *world) : Animal(5, 4, startingPoint, world) {
    abilityStrength = 0;
    abilityCooldown = 0;
}

char Human::getIcon() const {
    return 'H';
}

int Human::getStrength() const {
    return strength + abilityStrength;
}

void Human::activateAbility() {
    if (abilityCooldown > 5) {
        return;
    }
    Log::getInstance()->add(toString() + " activated ability");
    abilityStrength = 5;
    abilityCooldown = 5;
}

void Human::doTurn() {
    if (abilityCooldown > 0) {
        abilityCooldown--;
        Log::getInstance()->add(toString() + " ability cooldown: " + std::to_string(abilityCooldown));
        if (abilityCooldown == 0) {
            abilityStrength = 0;
        }
    }
    handleAbilityActivation();
    move(getMoveFromUser());
    age++;
}

// This whole thing was made minutes before presentation, so it's not the best code I've written
Point<int> Human::getMoveFromUser() {
    Console &c = *Console::getInstance();
    int yDrawCord = world->getHeight() + 3;
    Point<int> newPos = Point<int>(-1, -1);

    c.drawHorizontalLine(yDrawCord, 0, c.getWidth(), ' ');
    c << moveCursor(yDrawCord, 0) << "Use w/s/a/d keys to move. Location: " << position << flushBuffer;

    while (newPos == Point<int>(-1, -1)) {
        Point<int> direction = Point<int>(-1, -1);
        char key = ' ';
        while ((key = getch()) != ERR) {
            if (key == 'w' || key == 's' || key == 'a' || key == 'd') {
                break;
            }
        };
        switch (key) {
            case 'w':
                direction = Point<int>::UP;
                break;
            case 's':
                direction = Point<int>::DOWN;
                break;
            case 'a':
                direction = Point<int>::LEFT;
                break;
            case 'd':
                direction = Point<int>::RIGHT;
                break;
            default:
                c.drawHorizontalLine(yDrawCord, 0, c.getWidth(), ' ');
                c << moveCursor(yDrawCord, 0) << "Invalid key, use w/s/a/d keys to move" << flushBuffer;
                break;
        }
        newPos = translateDirectionToNewPosition(direction);
    }
    c.drawHorizontalLine(yDrawCord, 0, c.getWidth(), ' ');
    return newPos;
}

void Human::handleAbilityActivation() {
    Console &c = *Console::getInstance();
    int yDrawCord = world->getHeight() + 3;

    c.drawHorizontalLine(yDrawCord, 0, c.getWidth(), ' ');
    c << moveCursor(yDrawCord, 0) << "Press k if you want to activate ability" << flushBuffer;
    if (c.getChar() == 'k') {
        activateAbility();
    }
}

Point<int> Human::translateDirectionToNewPosition(Point<int> direction) const {
    if (direction == Point<int>(-1, -1)) {
        return Point<int>(-1, -1);
    }
    Point<int> newPos = position + direction;
    if (newPos.between(Point<int>::ZERO, world->getDimensions() - 1)) {
        return newPos;
    }
    return Point<int>(-1, -1);
}