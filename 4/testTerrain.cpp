#include "src/All.h"

#include <iostream>


int main() {
    Terrain terrain("cfg/terrain");
    std::cout << terrain;

    Summoner* s1 = terrain.summoners_.first;
    s1->SetRadius(10);

    Summoner* s2 = terrain.summoners_.second;
    s2->SetRadius(10);

    s1->Summon(_GeneralSquad, Point(2, 5));
    s2->Summon(_ImmoralHealingSquad, Point(97, 98));

    std::cout << terrain;
    return 0;
}

