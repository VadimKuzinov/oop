#pragma once
#include "Squads.h"
#include "Player.h"


class Game {
   Terrain* terrain_;
   std::pair<Player*, Player*> players_;

public:
    template <typename T>
    static menu(T* squad) {
        
    }

    Game(const std::string& filename) : 
                    terrain_(new Terrain(filename)), 
                    players_(std::make_pair<Player*, Player*>(new Player(terrain_->getSummonerFirst()), new Player(terrain_->getSummonerSecond()))) {
    }

    Player* getFirstPlayer() const {
        return players_.first;
    }

    Player* getSecondPlayer() const {
        return players_.second;
    }
};

