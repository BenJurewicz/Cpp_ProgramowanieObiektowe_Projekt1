#include "console.h"
#include "world.h"
#include "rng.h"

int main() {
    Log::init(10);
    Console::init();
    Rng::init();

    Console &console = *Console::getInstance();
    console << moveCursor(0, 1) << "Benjamin Jurewicz s198326" << flushBuffer;

    int worldWidth = 20;
    int worldHeight = 20;
    World world(worldHeight, worldWidth);

    world.startLoopNoInput(console, 50);
//    char key = console.getChar();

    console << flushBuffer;
    console.refreshWindow();

    Console::destroyInstance();
    Log::destroyInstance();
    return 0;
}
