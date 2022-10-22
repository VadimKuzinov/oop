#pragma once
#include "Base.h"
#include <memory>


class IActive {
protected:
    std::shared_ptr<Base> captured_ = nullptr;
    Point target_coords_;

public:
    void setCaptured(std::shared_ptr<Base> captured) {
        captured_ = captured;
    }

    void setTargetCoords(Point target_coords) {
        target_coords_ = target_coords;
    }
};

