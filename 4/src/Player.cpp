#include "Player.h"


void Player::catchClick(Point where) {
    if (where.y >= terrain_->getMap().getHeight() || where.x >= terrain_->getMap().getWidth()) {
        return;
    }

    if (active_ == nullptr) {
        setActive(where);
    }
    else if (active_ == terrain_->getMap()[where]) {
        active_ = nullptr;
    }
    else {
        auto casted = std::dynamic_pointer_cast<Obstacle>(active_);
        casted->setTargetCoords(where);
        casted->setCaptured(terrain_->getMap()[where]);
    }
}


