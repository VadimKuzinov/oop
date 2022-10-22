#pragma once
#include <iostream>
#include <cmath>


struct Point {
    double x;
    double y;

    static Point withIntCfs(const Point& p) {
        return {static_cast<double>(lround(p.x)), static_cast<double>(lround(p.y))};
    }

    static double distance(const Point& p1, const Point& p2) {
        return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }

    static Point normalized(const Point& p) {
        auto len = distance(p, Point{0, 0});
        return {p.x / len, p.y / len};
    }
};


std::istream& operator>>(std::istream& is, Point& p);
std::ostream& operator<<(std::ostream& os, const Point& p);

inline bool operator==(const Point& p1, const Point& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

inline Point operator-(const Point& p1, const Point& p2) {
    return {p1.x - p2.x, p1.y - p2.y};
}

inline Point operator+(const Point& p1, const Point& p2) {
    return {p1.x + p2.x, p1.y + p2.y};
}

inline Point operator*(const Point& p, int cf) {
    return {p.x * cf, p.y * cf};
}

namespace std {
    template <>
    struct hash<Point> {
        std::size_t operator()(const Point& p) const {
            return hash<double>()(p.x) ^ hash<double>()(p.y);
        }
    };
}
