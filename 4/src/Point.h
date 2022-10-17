#pragma once

#include <iostream>


struct Point {
    double x;
    double y;
};


std::istream& operator>>(std::istream& is, Point& p);
std::ostream& operator<<(std::ostream& os, const Point& p);
bool operator==(const Point& p1, const Point& p2);
double operator-(const Point& p1, const Point& p2);

namespace std {
    template <>
    struct hash<Point> {
        std::size_t operator()(const Point& p) const {
            return hash<double>()(p.x) ^ hash<double>()(p.y);
        }
    };
}
