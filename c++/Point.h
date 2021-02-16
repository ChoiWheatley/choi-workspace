#ifndef POINT_H
#define POINT_H 1

#include <stdexcept>

namespace Graph_lib
{

struct Point {
    int x, y;
    Point(int xx, int yy) : x{xx}, y{yy} { 
        if (x < 0 || y < 0) throw std::runtime_error("Point cannot be smaller than 0");
    }
    Point() : x{0}, y{0} { }

    Point& operator+=(Point d) { x+=d.x; y+=d.y; return *this; }
    Point& operator=(Point d) { x = d.x, y = d.y; return *this; }
};// struct Point

inline bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }
inline bool operator!=(Point a, Point b) { return !(a==b); }

}// namespace Graph_lib

#endif
