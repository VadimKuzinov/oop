#pragma once

#include "Point.h"

#include <unordered_set>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>


class Summoner;
class BasicSquad;

class Terrain {
public:
    std::unordered_set<Point> obstacles_;
   
    std::pair<Summoner*, Summoner*> summoners_;
    std::vector<std::vector<BasicSquad*>> map_;
    std::list<BasicSquad*> squads_;

    static BasicSquad* obstacle_; 

    friend std::istream& operator>>(std::istream& is, Terrain& terrain);
    friend std::ostream& operator<<(std::ostream& os, const Terrain& terrain);

public:
    int MAX_X;
    int MAX_Y;

public:
    Terrain(const std::string& cfg_filename); //add
    ~Terrain();
};


std::istream& operator>>(std::istream& is, Terrain& terrain);
std::ostream& operator<<(std::ostream& os, const Terrain& terrain);

