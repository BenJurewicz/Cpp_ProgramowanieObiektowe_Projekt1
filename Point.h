#ifndef PROJEKT1CPP_POINT_H
#define PROJEKT1CPP_POINT_H

#include "rng.h"
#include "console.h"

/**
 * Holds a pair of coordinates (x, y) of type T.
 * @tparam T must be a numeric type (int, float, double, etc.)
 */
template<typename T>
class Point {
    T _x, _y;
public:
    static Point<T> randomPoint(T maxX, T maxY, T minX = 0, T minY = 0) {
        return Point<T>(
                Rng::intFromRange(minX, maxX),
                Rng::intFromRange(minY, maxY)
        );
    }

    Point() {
        _x = 0;
        _y = 0;
    }

    Point(T x, T y) {
        this->_x = x;
        this->_y = y;
    }

    void setX(T x) {
        this->_x = x;
    }

    void setY(T y) {
        this->_y = y;
    }

    T getX() const {
        return _x;
    }

    T x() const {
        return _x;
    }

    T getY() const {
        return _y;
    }

    T y() const {
        return _y;
    }

    [[nodiscard]] std::string toString() const {
        return "P(" + std::to_string(_x) + ", " + std::to_string(_y) + ")";
    }

    Point<T> operator+(const Point<T> &other) const {
        return Point<T>(_x + other._x, _y + other._y);
    }

    Point<T> operator-(const Point<T> &other) const {
        return Point<T>(_x - other._x, _y - other._y);
    }

    bool operator==(const Point<T> &other) const {
        return _x == other._x && _y == other._y;
    }

    bool operator!=(const Point<T> &other) const {
        return _x != other._x || _y != other._y;
    }

    bool operator<(const Point<T> &other) const {
        return _x < other._x || _y < other._y;
    }

    bool operator<=(const Point<T> &other) const {
        return _x <= other._x || _y <= other._y;
    }

    bool operator>(const Point<T> &other) const {
        return _x > other._x || _y > other._y;
    }

    bool operator>=(const Point<T> &other) const {
        return _x >= other._x || _y >= other._y;
    }

    static const Point<T> UP, DOWN, LEFT, RIGHT, ZERO;
};

Console &operator<<(Console &console, const Point<int> &point);

template<typename T>
const Point<T> Point<T>::UP = Point<T>(0, -1);

template<typename T>
const Point<T> Point<T>::DOWN = Point<T>(0, 1);

template<typename T>
const Point<T> Point<T>::LEFT = Point<T>(-1, 0);

template<typename T>
const Point<T> Point<T>::RIGHT = Point<T>(1, 0);

template<typename T>
const Point<T> Point<T>::ZERO = Point<T>(0, 0);

#endif //PROJEKT1CPP_POINT_H
