#include "src/Terrain.h"
#include "src/Summoner.h"

#include <iostream>


int main() {
    Terrain terrain("cfg/terrain");
    std::cout << terrain;

    auto s1 = terrain.getSummonerFirst();
    auto s2 = terrain.getSummonerSecond();
    s1->setTargetCoords(Point(2, 5));
    s1->setSummonedId(General_);
    s1->tryToSummon();
    s1->summon();

    std::cout << terrain;

    return 0;
}

