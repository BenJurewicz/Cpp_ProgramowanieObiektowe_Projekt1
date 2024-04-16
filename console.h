#ifndef PROJEKT1CPP_CONSOLE_H
#define PROJEKT1CPP_CONSOLE_H

#include <string>
#include <ncurses.h>
#include <sstream>
#include <functional>

constexpr int windowWidth = 80;
constexpr int windowHeight = 20;

typedef enum {
    WhiteOnBlack=1,
    GreenOnBlack,
} Color;

class Console {
    static Console* instance;
    std::stringstream printBuffer;

    WINDOW *win{};
    bool hasColors{};
    int winWidth;
    int winHeight;

    void createColorPairs();
    void initColors();
    void initNcurses();

    Console();
public:


    static Console *getInstance();

    void refreshWindow();

    void mvPutCh(int y, int x, char ch);

    std::string getStringFromUser();
    char getChar();

//    Console& operator<<(const std::function<Console&(Console&)> &func);
//    Console& operator<<(const Color& color);
    Console& operator<<(std::ostream &(*func)(std::ostream &)); // this is for std::endl to flush
    friend std::function<Console&(Console&)> moveCursor(int y, int x);
//    friend Console& flushBuffer(Console& console);

    template<typename T>
    Console& operator<<(const T &value) {
        printBuffer << value;
        return *this;
    }

    ~Console();
};

template<>
inline Console& Console::operator<< <std::function<Console&(Console&)> >(const std::function<Console&(Console&)> &value){
    value(*this);
    return *this;
}

template<>
inline Console& Console::operator<<<Color>(const Color& value){
    if(hasColors){
        wattron(win, COLOR_PAIR(value));
    }
    return *this;
}

std::function<Console&(Console&)> moveCursor(int y, int x);
//Console& flushBuffer(Console& console);

#endif //PROJEKT1CPP_CONSOLE_H
