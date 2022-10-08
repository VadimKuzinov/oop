#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Curve.h"


long double Curve::GetRBig(long double alpha) const noexcept {
    return std::fabs(a_ / cos(alpha)) + l_;
}

long double Curve::GetRSmall(long double alpha) const noexcept {
    return std::fabs(std::fabs(a_ / cos(alpha)) - l_);
}

long double Curve::GetY(long double x) const noexcept {
    auto temp = l_ * (x / (x + a_));
    return std::sqrt((temp - x) * (temp + x));
}

long double Curve::GetCurvature(long double x) const noexcept {
    auto sqr = [](long double arg) { return arg * arg; };
    long double phi = acos((x + a_) / l_);

    long double num = -2 * a_ * l_ * sqr(tan(phi)) / cos(phi) - a_ * l_ / cos(phi) + sqr(l_);
    long double den = sqr(l_) + sqr(a_ / sqr(cos(phi))) - 2 * a_ * l_ / cos(phi);
    den *= sqrt(den);

    return num / den;
}

long double Curve::GetLoopS() const noexcept {
    long double fraction = a_ / l_;
    long double bound = acos(fraction);
    long double sinBound = sqrt(1 - fraction * fraction);
    long double pi = 3.14159265358979323846L;
    long double absIntegralAtBound = -0.5 * a_ * l_ * (1 - sinBound == 0 ? 0 : log((1 + sinBound) / (1 - sinBound))) + l_ * a_ * sinBound + 0.5 * l_ * l_ * bound - 0.5 * l_ * l_ * sinBound * fraction;
    if (a_ > 0) {
        return absIntegralAtBound;
    }
    return 0.5 * l_ * l_ * pi - absIntegralAtBound;
}

std::vector<long double> Curve::GetInflections() const noexcept {
    long double pi = 3.14159265358979323846L;
    long double left;
    long double right;
    std::vector<std::pair<long double, long double>> boundPairs;
    if (a_ > 0) {
        left = -a_ - l_;
        right = -a_;
        boundPairs.push_back(std::make_pair(left, right));
        if (a_ > l_) {
            left = -a_;
            right = -a_ + l_;
            boundPairs.push_back(std::make_pair(left, right));
        }
    }
    else {
        left = -a_;
        right = -a_ + l_;
        boundPairs.push_back(std::make_pair(left, right));
        if (-a_ > l_) {
            left = -a_ - l_;
            right = -a_;
            boundPairs.push_back(std::make_pair(left, right));
        }
    }

    long double val = a_ / l_;
    auto sqr = [](long double arg) { return arg * arg; };
    auto f = [this, val, &sqr](long double arg) { return 2 * val * sqr(tan(acos((arg + a_) / l_))) + (arg + a_) / l_ - val; };
    auto epsX = 1e-7;
    auto epsY = 1e-5;

    long double mid;
    std::vector<long double> result;
    for (auto [left, right] : boundPairs) {
        mid = (left + right) / 2;
        bool descending = f(mid) > f(mid + epsX);
        while (right - left > epsX) {
            if (f(mid) > 0) {
                (descending ? left : right) = mid;
            }
            else {
                (descending ? right : left) = mid;
            }
            mid = (left + right) / 2;
        }
        if (f(mid) - 0 < epsY) {
            result.push_back(mid);
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}

void Curve::Print() const noexcept {
    std::cout << l_ * l_ << "x^2 = " << "(x^2 + y^2)(y + " << a_ << ")^2" << std::endl;
}
