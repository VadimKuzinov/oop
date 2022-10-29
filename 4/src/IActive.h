#pragma once
#include "Obstacle.h"
#include <memory>


class IActive {
protected:
    std::shared_ptr<Obstacle> captured_ = nullptr;
    Point target_coords_;

public:
    void setCaptured(std::shared_ptr<Obstacle> captured) {
        captured_ = captured;
    }

    void setTargetCoords(Point target_coords) {
        std::cout << "Setting target coords: " << target_coords << '\n';
        target_coords_ = target_coords;
    }
};

