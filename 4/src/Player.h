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
        std::cout << where << std::endl;
        if (where.y >= terrain_->MAX_Y || where.x >= terrain_->MAX_X) {
            std::cout << "Out of range of the map" << std::endl;
            return;
        }

        active_ = terrain_->map_[where.y][where.x];
        if (active_ == nullptr) {
            std::cout << "Set to nullptr" << std::endl;
        }
        else {
            std::cout << "Set to: " << active_->getId() << std::endl;
        }
    }

    std::shared_ptr<Entity> getActive() const {
        return active_;
    }

    void catchClick(Point where) {
        if (active_ == nullptr || active_->getId() == Obstacle_) {
            setActive(where);
        }
        else if (active_->getId() != Obstacle_) {
            auto casted = std::dynamic_pointer_cast<Summoner>(active_);
            if (casted == nullptr) {
                std::cout << "dynamic_casted to nullptr???" << std::endl;
                return;
            }
            casted->setTargetCoords(where);
        }
    }

    std::shared_ptr<Summoner> getSummoner() const {
        return summoner_;
    }
    //class Game{ ... some method() {player1->setActive()}....}  
};

