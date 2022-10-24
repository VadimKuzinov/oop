#pragma once
#include "Squads.h"
#include "Player.h"
#include "Utils.h"
#include <vector>


class Game {
   Terrain* terrain_;
   std::pair<Player*, Player*> players_;

public:
    template <typename T>
    static auto menu(T* squad) {
        std::vector<std::pair<void (*)(T*), const char*>> choices; 
        if constexpr (Attacking<T>) {
            choices.push_back(std::make_pair([](T* squad){ squad->tryToAttack(); }, "Attack"));
        }
		if constexpr (Moving<T>) {
			choices.push_back(std::make_pair([](T* squad){ squad->tryToMove(); }, "Move"));
		}
		if constexpr (Attacking<T>) {
			choices.push_back(std::make_pair([](T* squad){ squad->tryToAttack(); }, "Attack"));
		}
		if constexpr (Summoning<T>) {
			choices.push_back(std::make_pair([](T* squad){ squad->tryToSummon(); }, "Summon"));
		}
		if constexpr (Accumulating<T>) {
			choices.push_back(std::make_pair([](T* squad){ squad->tryToAccumulate(); }, "Accumulate"));
		}
		if constexpr (Upgrading<T>) {
			choices.push_back(std::make_pair([](T* squad){ squad->tryToUpgrade(); }, "Upgrade"));
		}
		if constexpr (Healing<T>) {
			choices.push_back(std::make_pair([](T* squad){ squad->tryToHeal(); }, "Heal"));
		}
		if constexpr (Capturing<T>) {
			choices.push_back(std::make_pair([](T* squad){ squad->tryToCapture(); }, "Capture"));
		}

        return choices;
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

