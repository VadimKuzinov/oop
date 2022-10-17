#include "Point.h"
#include <cmath>


bool operator==(const Point& p1, const Point& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

std::istream& operator>>(std::istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << '{' << p.x << ", " << p.y << '}';
    return os;
}

double operator-(const Point& p1, const Point& p2) {
    return sqrt(p1.x * p1.x + p2.x * p2.x);
}

