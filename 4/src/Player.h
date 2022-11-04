#pragma once
#include "Squads.h"
#include <memory>
#include <iostream>


class Player {
    std::shared_ptr<Summoner> summoner_;
    Terrain* terrain_;
    std::shared_ptr<Entity> active_ = nullptr;

public:
    Player(const std::shared_ptr<Summoner>& summoner) : summoner_(summoner), terrain_(summoner->getTerrain()) {
    }

    void setActive(Point where) {
        std::cout << "Inside set active" << std::endl;
        active_ = terrain_->map_[where.y][where.x];
    }

    void resetActive() {
        active_ = nullptr;
    }

    std::shared_ptr<Entity> getActive() const {
        return active_;
    }

    void catchClick(Point where) {
        if (terrain_ == nullptr) std::cout << "TERRAIN IS NULLPTR" << std::endl;
        std::cout << "Catched click: ";
        std::cout << where << std::endl;
        if (where.y >= terrain_->MAX_Y || where.x >= terrain_->MAX_X) {
            std::cout << "INSIDE IF" << std::endl;
            return;
        }
        std::cout << "IN RANGE" << std::endl;

        if (active_ == nullptr) {
            std::cout << "before setActive()" << std::endl;
            setActive(where);
            std::cout << "After" << std::endl;
        }
        else if (active_ == terrain_->map_[where.y][where.x]) {
            active_ = nullptr;
        }
        else {
            auto casted = std::dynamic_pointer_cast<Obstacle>(active_);
            casted->setTargetCoords(where);
            casted->setCaptured(terrain_->map_[where.y][where.x]);
        }
    }

    std::shared_ptr<Summoner> getSummoner() const {
        return summoner_;
    }
};

