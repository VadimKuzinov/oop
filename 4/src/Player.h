#pragma once
#include "Summoner.h"
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
        active_ = terrain_->getMap()[where];
    }

    void resetActive() {
        active_ = nullptr;
    }

    std::shared_ptr<Entity> getActive() const {
        return active_;
    }

    void catchClick(Point where);

    std::shared_ptr<Summoner> getSummoner() const {
        return summoner_;
    }
};

