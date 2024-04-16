#include "console.h"

int main() {
    Console* console = Console::getInstance();
//    *console << moveCursor(1,2) << Color::GreenOnBlack << "hello world" << fb();
    *console << moveCursor(1,2) << Color::GreenOnBlack /*<< "hello world"*/;
    *console << moveCursor(1,2) << Color::GreenOnBlack << "hello world";
    *console << flushBuffer;
    console->refreshWindow();
    return 0;
}
