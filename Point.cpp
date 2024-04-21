#include "Point.h"

Console &operator<<(Console &console, const Point<int> &point) {
//    console << "P(" << point.getX() << ", " << point.getY() << ")";
    console << point.toString();
    return console;
}
