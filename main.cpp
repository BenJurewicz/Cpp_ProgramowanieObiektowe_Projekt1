#include "console.h"
#include "world.h"
#include "rng.h"

#include "creatures/animals/wolf.h"

int main() {
    Log::init(17);
    Console::init();
    Console &console = *Console::getInstance();

    int worldWidth = 20;
    int worldHeight = 20;
    World world(worldHeight, worldWidth);

//    world.drawMap(console, 1, 1);
    world.startLoopNoInput(console, 50);
//    Wolf w(Point<int>(0, 0), &world);
//    //generate a for loop that repeates 4 times
//    for (int i = 0; i < 4; i++) {
//        console << moveCursor(i + 1, 1) << w.getRandomCorrectNeighbour(false) << flushBuffer;
//        /* output from this
//        P(0, 1)
//        P(-1, 0)
//        P(-1, 0)
//        P(-1, 0)
//        */
//    }

    console << flushBuffer;
    console.refreshWindow();

    Console::destroyInstance();
    Log::destroyInstance();
    return 0;
}
