#pragma once
#include "Point.h"
#include "Squads.h"
#include "Player.h"
#include "Utils.h"
#include <vector>
#include <thread>
#include <string>
#include <sstream>
#include <iostream>


class Game {
    Terrain* terrain_;
    std::pair<Player*, Player*> players_;
    int sfd; 
    int connfd;

    void initializeSocket();

public:
    template <typename T>
    static auto menu(T* squad) {
        std::vector<std::pair<void (*)(Entity*), const char*>> choices; 
        if constexpr (Attacking<T>) {
            choices.push_back(std::make_pair([](Entity* squad){ dynamic_pointer_cast<T>(squad)->tryToAttack(); }, "Attack"));
        }
		if constexpr (Moving<T>) {
			choices.push_back(std::make_pair([](Entity* squad){ dynamic_pointer_cast<T>(squad)->tryToMove(); }, "Move"));
		}
		if constexpr (Summoning<T>) {
			choices.push_back(std::make_pair([](Entity* squad){ dynamic_pointer_cast<T>(squad)->tryToSummon(); }, "Summon"));
		}
		if constexpr (Accumulating<T>) {
			choices.push_back(std::make_pair([](Entity* squad){ dynamic_pointer_cast<T>(squad)->tryToAccumulate(); }, "Accumulate"));
		}
		if constexpr (Upgrading<T>) {
			choices.push_back(std::make_pair([](Entity* squad){ dynamic_pointer_cast<T>(squad)->tryToUpgrade(); }, "Upgrade"));
		}
		if constexpr (Healing<T>) {
			choices.push_back(std::make_pair([](Entity* squad){ dynamic_pointer_cast<T>(squad)->tryToHeal(); }, "Heal"));
        }

        return choices;
    }

    Game(const std::string& filename) : 
                    terrain_(new Terrain(filename)), 
                    players_(std::make_pair<Player*, Player*>(new Player(terrain_->getSummonerFirst()), new Player(terrain_->getSummonerSecond()))) {
//        initializeSocket();                        
    }

    Player* getFirstPlayer() const {
        return players_.first;
    }

    Player* getSecondPlayer() const {
        return players_.second;
    }

    Terrain* getTerrain() const {
        return terrain_;
    }

    void catchClicks();
    void run(); 
    
};

