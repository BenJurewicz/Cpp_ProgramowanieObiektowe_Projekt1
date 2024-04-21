#include "Point.h"

Console &operator<<(Console &console, const Point<int> &point) {
    console << point.toString();
    return console;
}
