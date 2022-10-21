#pragma once

#include <iostream>


struct Point {
    double x;
    double y;

    static Point withIntCfs(const Point& p) {
        return {static_cast<int>(p1.x), static_cast<int>(p1.y)};
    }

    static double distance(const Point&, const Point&) {
        return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }

    static Point normalized(const Point& p) {
        auto len = distance(p, Point{0, 0});
        return {p1.x / len, p1.y / len};
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
    return (p1.x + p2.x, p1.y + p2.y};
}

inline Point operator*(const Point& p, int cf) {
    return {p1.x * cf, p1.y * cf};
}

namespace std {
    template <>
    struct hash<Point> {
        std::size_t operator()(const Point& p) const {
            return hash<double>()(p.x) ^ hash<double>()(p.y);
        }
    };
}
