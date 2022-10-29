#include "src/Game.h"
#include "src/Terrain.h"
#include "src/Summoner.h"

#include <iostream>


int main() {
    Game game("cfg/terrain");
    auto terrain = game.getTerrain();

    auto s1 = terrain->getSummonerFirst();
    auto s2 = terrain->getSummonerSecond();
    s1->setTargetCoords(Point(2, 5));
    s1->setSummonedId(MoralHealing_);
    s1->tryToSummon();
    s1->summon();
    
    auto menu = Game::menu(std::dynamic_pointer_cast<MoralHealingSquad>(terrain->map_[5][2]));
    for (auto&& [fun_ptr, what] : menu) {
        std::cout << what << std::endl;
    }

    std::cout << *terrain;
    game.run();

    return 0;
}

