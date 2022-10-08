#pragma once
#include <vector>


class Curve {
private:
    long double l_;
    long double a_;

public:
    Curve() noexcept : l_(0), a_(0) {
    }

    Curve(long double l, long double a) noexcept : l_(l > 0 ? l : -l), a_(a) {
    }

    void SetL(long double l) noexcept {
        l_ = l > 0 ? l : -l;
    }

    void SetA(long double a) noexcept {
        a_ = a;
    }

    long double GetL() const noexcept {
        return l_;
    }

    long double GetA() const noexcept {
        return a_;
    }

    long double GetRBig(long double alpha) const noexcept;

    long double GetRSmall(long double alpha) const noexcept;

    long double GetY(long double x) const noexcept;

    long double GetCurvature(long double x) const noexcept;

    long double GetLoopS() const noexcept;

    std::vector<long double> GetInflections() const noexcept;

    void Print() const noexcept;
};
