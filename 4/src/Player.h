#pragma once
#include "Squads.h"
#include <memory>


class Player {
    std::shared_ptr<Summoner> summoner_;
    Terrain* terrain_;
    std::shared_ptr<Base> active_ = nullptr;

public:
    Player(const std::shared_ptr<Summoner>& summoner) : summoner_(summoner), terrain_(summoner->getTerrain()) {
    }

    void setActive(Point where) {
        active_ = terrain_->map_[where.y][where.x];
    }
    //class Game{ ... some method() {player1->setActive()}....}  
};

