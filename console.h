#ifndef PROJEKT1CPP_CONSOLE_H
#define PROJEKT1CPP_CONSOLE_H

#include <string>
#include <ncurses.h>
#include <sstream>
#include <functional>

constexpr int windowWidth = 80;
constexpr int windowHeight = 20;

/**
 * @brief Pass to the Console stream operator to change the color of the text
 */
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

    Console& operator<<(std::ostream &(*func)(std::ostream &)); // this is for std::endl to flush

    Console& operator<<(Console& (*value)(Console&));

    template<typename T>
    Console& operator<<(const T &value) {
        printBuffer << value;
        return *this;
    }

    friend std::function<Console&(Console&)> moveCursor(int y, int x);
    friend Console& flushBuffer(Console& console);

    ~Console();
};

template<>
inline Console& Console::operator<< <Console& (*)(Console&) >(Console& (* const &value)(Console&)){
    value(*this);
    return *this;
}

template<>
inline Console& Console::operator<< <std::function<Console&(Console&)> >(const std::function<Console&(Console&)> &value){
    return value(*this);
}

template<>
inline Console& Console::operator<<<Color>(const Color& value){
    if(hasColors){
        wattron(win, COLOR_PAIR(value));
    }
    return *this;
}

/**
 * @brief Creates a function that moves the cursor to the specific location on the screen when applied to a Console object
 * @param y y coordinate where the cursor should be moved
 * @param x x coordinate where the cursor should be moved
 * @return the same Console object
 */
std::function<Console&(Console&)> moveCursor(int y, int x);

/**
 * @brief Flushes the buffer of the Console object to the screen
 * @param console
 * @return the same Console object
 */
Console& flushBuffer(Console& console);

#endif //PROJEKT1CPP_CONSOLE_H
