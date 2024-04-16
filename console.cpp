#include "console.h"


#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
void Console::createColorPairs(){
    init_pair(WhiteOnBlack, COLOR_WHITE, COLOR_BLACK);
    init_pair(GreenOnBlack, COLOR_GREEN, COLOR_BLACK);
}
#pragma clang diagnostic pop

void Console::initColors(){
    if(!has_colors()){
        hasColors = false;
        return;
    }
    hasColors = true;
    start_color();
    createColorPairs();
}

void Console::initNcurses(){
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    initColors();
}

Console::Console() {
    winWidth = windowWidth;
    winHeight = windowHeight;

    initNcurses();

    win = newwin(winHeight, winWidth, 0, 0);
}

Console* Console::instance = nullptr;
Console* Console::getInstance() {
    if(instance == nullptr) {
        instance = new Console();
    }
    return instance;
}

void Console::refreshWindow() {
    wrefresh(win);
}

//void Console::mvPrintf(int y, int x, const char *text, ...){
//    va_list args;
//    va_start(args, text);
//    mvwprintw(win, y, x, text, args);
////    waddstr(win, str);
//    va_end(args);
//}

void Console::mvPutCh(int y, int x, char ch){
    mvwaddch(win, y, x, ch);
}

std::string Console::getStringFromUser() {
    echo();
    curs_set(1);
    nocbreak();

//    wgetnstr(win, fileName, 50 - 1);
    std::string input;
    getch();
    char ch = getChar();
    while(ch != '\n') {
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
//    return (char)wgetch(win);
}
#pragma clang diagnostic pop

Console::~Console() {
    echo();
    curs_set(1);
    cbreak();
    delwin(win);
    endwin();
}

//Console& Console::operator<<(const Color& color){
//    if(hasColors){
//        wattron(win, COLOR_PAIR(color));
//    }
//    return *this;
//}


Console& Console::operator<<(std::ostream &(*func)(std::ostream &)){
    // TODO: remake this so it will work with flushBuffer instead of std::endl
    waddstr(win, printBuffer.str().c_str());
    printBuffer.str("");
    printBuffer.clear();
    refreshWindow(); // TODO: probbably should remove this
    return *this;
}

//Console &Console::operator<<(const std::function<Console &(Console &)> &func) {
//    func(*this);
//    return *this;
//}

std::function<Console&(Console&)> moveCursor(int y, int x) {
    return [=](Console& console) -> Console& {
        wmove(console.win, y, x);
        return console;
    };
}

//Console& flushBuffer(Console& console) {
//    waddstr(console.win, console.printBuffer.str().c_str());
//    console.printBuffer.str("");
//    console.printBuffer.clear();
//    console.refreshWindow();
//    return console;
//}

