#include "console.h"

int main() {
    Console* console = Console::getInstance();
    *console << moveCursor(1,2) << Color::GreenOnBlack << "hello world" << std::endl;
    console->refreshWindow();
    return 0;
}
