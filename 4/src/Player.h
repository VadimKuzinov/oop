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
        active_ = terrain_->map_[where.y][where.x];
    }

    void resetActive() {
        active_ = nullptr;
    }

    std::shared_ptr<Entity> getActive() const {
        return active_;
    }

    void catchClick(Point where) {
        if (where.y >= terrain_->MAX_Y || where.x >= terrain_->MAX_X) {
            return;
        }
    
        if (active_ == nullptr) {
            setActive(where);
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

