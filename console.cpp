#include "console.h"

std::unique_ptr<Console> Console::instance = nullptr;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"

void Console::createColorPairs() {
    init_pair(WhiteOnBlack, COLOR_WHITE, COLOR_BLACK);
    init_pair(GreenOnBlack, COLOR_GREEN, COLOR_BLACK);
}

#pragma clang diagnostic pop

[[maybe_unused]] void Console::initColors() {
    if (!has_colors()) {
        hasColors = false;
        return;
    }
    hasColors = true;
    start_color();
    createColorPairs();
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"

void Console::initNcurses() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
//    initColors();
}

#pragma clang diagnostic pop

Console::Console(int width, int height) {
    winWidth = width;
    winHeight = height;

    initNcurses();

    win = newwin(winHeight, winWidth, 0, 0);
}

Console *Console::init(int width, int height) {
    if (instance == nullptr) {
        instance = std::unique_ptr<Console>(new Console(width, height));
    }
    return instance.get();
}

Console *Console::getInstance() {
    if (instance == nullptr) {
        throw std::runtime_error("Console has not been initialized");
    }
    return instance.get();
}

void Console::refreshWindow() {
    wrefresh(win);
}

[[maybe_unused]] void Console::drawChar(int y, int x, char ch) {
    mvwaddch(win, y, x, ch);
}

void Console::drawHorizontalLine(int y, int x, int length, chtype character) {
    mvwhline(win, y, x, character, length);
}

void Console::drawVerticalLine(int y, int x, int length, chtype character) {
    mvwvline(win, y, x, character, length);
}

[[maybe_unused]] void Console::drawBorder(int y, int x, int height, int width, const std::string &title) {
    drawHorizontalLine(y, x, width - 1, ACS_HLINE);
    drawHorizontalLine(y + height - 1, x, width - 1, ACS_HLINE);

    drawVerticalLine(y, x, height - 1, ACS_VLINE);
    drawVerticalLine(y, x + width - 1, height - 1, ACS_VLINE);

    mvwaddch(win, y, x, ACS_ULCORNER);
    mvwaddch(win, y, x + width - 1, ACS_URCORNER);
    mvwaddch(win, y + height - 1, x, ACS_LLCORNER);
    mvwaddch(win, y + height - 1, x + width - 1, ACS_LRCORNER);

    if (!title.empty()) {
        mvwaddstr(win, y, x + 1, title.c_str());
    }
}

void Console::drawRectangle(int y, int x, int height, int width, chtype character) {
    for (int i = 0; i < height; i++) {
        drawHorizontalLine(y + i, x, width, character);
    }
}

[[maybe_unused]] std::string Console::getStringFromUser() {
    echo();
    curs_set(1);
    nocbreak();

//    wgetnstr(win, fileName, 50 - 1);
    std::string input;
    getch();
    char ch = getChar();
    while (ch != '\n') {
        input.push_back(ch);
        ch = getChar();
    }

    noecho();
    curs_set(0);
    cbreak();

    return input;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"

inline char Console::getChar() {
    return getch();
//    return (char) wgetch(win);
}

#pragma clang diagnostic pop

Console &Console::operator<<(Console &(*value)(Console &)) {
    value(*this);
    return *this;
}

Console::~Console() {
    echo();
    curs_set(1);
    cbreak();
    delwin(win);
    endwin();
}

std::function<Console &(Console &)> moveCursor(int y, int x) {
    return [&](Console &console) -> Console & {
        wmove(console.win, y, x);
        return console;
    };
}

Console &flushBuffer(Console &console) {
    waddstr(console.win, console.printBuffer.str().c_str());
    console.printBuffer.str("");
    console.printBuffer.clear();
    console.refreshWindow();
    return console;
}

Console &clearBuffer(Console &console) {
    console.printBuffer.str("");
    console.printBuffer.clear();
    return console;
}

int Console::getWidth() const {
    return winWidth;
}

int Console::getHeight() const {
    return winHeight;
}

void Console::destroyInstance() {
    instance.reset();
}

