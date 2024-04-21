#ifndef PROJEKT1CPP_CONSOLE_H
#define PROJEKT1CPP_CONSOLE_H

#include <string>
#include <ncurses.h>
#include <sstream>
#include <functional>

//constexpr int windowWidth = 100;
//constexpr int windowHeight = 60;

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

    [[maybe_unused]] void initColors();
    void initNcurses();

    Console(int width, int height);
public:
    static Console* init(int width = 100, int height = 60);
    static Console* getInstance();
    static void destroyInstance();

    int getWidth() const;
    int getHeight() const;

    void refreshWindow();

    [[maybe_unused]] void drawChar(int y, int x, char ch);

    /**
     *  @Note There are special ncurses characters that can be use used instead of chars
     *  Special characters list:
     *  <ul>
     *     <li> ACS_HLINE: Horizontal line </li>
     *     <li> ACS_VLINE: Vertical line </li>
     *     <li> ACS_ULCORNER: Upper left-hand corner </li>
     *     <li> ACS_URCORNER: Upper right-hand corner </li>
     *     <li> ACS_LLCORNER: Lower left-hand corner </li>
     *     <li> ACS_LRCORNER: Lower right-hand corner </li>
     *     <li> ACS_LTEE: Tee pointing right </li>
     *     <li> ACS_RTEE: Tee pointing left </li>
     *     <li> ACS_BTEE: Tee pointing up </li>
     *     <li> ACS_TTEE: Tee pointing down </li>
     *     <li> ACS_PLUS: Large plus or crossover </li>
     *  </ul>
     */
    void drawHorizontalLine(int y, int x, int length, chtype character = 0);

    /**
     *  @Note There are special ncurses characters that can be use used instead of chars
     *  Special characters list:
     *  <ul>
     *     <li> ACS_HLINE: Horizontal line </li>
     *     <li> ACS_VLINE: Vertical line </li>
     *     <li> ACS_ULCORNER: Upper left-hand corner </li>
     *     <li> ACS_URCORNER: Upper right-hand corner </li>
     *     <li> ACS_LLCORNER: Lower left-hand corner </li>
     *     <li> ACS_LRCORNER: Lower right-hand corner </li>
     *     <li> ACS_LTEE: Tee pointing right </li>
     *     <li> ACS_RTEE: Tee pointing left </li>
     *     <li> ACS_BTEE: Tee pointing up </li>
     *     <li> ACS_TTEE: Tee pointing down </li>
     *     <li> ACS_PLUS: Large plus or crossover </li>
     *  </ul>
     */
    void drawVerticalLine(int y, int x, int length, chtype character = 0);

    [[maybe_unused]] void drawBorder(int y, int x, int height, int width, const std::string& title = "");
    [[maybe_unused]] void drawRectangle(int y, int x, int height, int width, chtype character = ' ');

    [[maybe_unused]] std::string getStringFromUser();
    [[maybe_unused]] char getChar();

    Console& operator<<(Console& (*value)(Console&));

    template<typename T>
    Console& operator<<(const T &value) {
        printBuffer << value;
        return *this;
    }

    friend std::function<Console&(Console&)> moveCursor(int y, int x);
    friend Console& flushBuffer(Console& console);
    friend Console& clearBuffer(Console& console);

    ~Console();
};

template<> // This is needed for flushBuffer
inline Console& Console::operator<< <Console& (*)(Console&) >(Console& (* const &value)(Console&)){
    value(*this);
    return *this;
}

template<> // This is needed for moveCursor
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

Console& clearBuffer(Console& console);

#endif //PROJEKT1CPP_CONSOLE_H
