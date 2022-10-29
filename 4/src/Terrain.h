#pragma once
#include "Point.h"
#include "Type.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <memory>


class Terrain;
class Summoner;
class Entity;

std::istream& operator>>(std::istream& is, Terrain& terrain);
std::ostream& operator<<(std::ostream& os, const Terrain& terrain);


class Terrain {
public:
    std::pair<Point, Point> summoners_coords_;
    std::vector<std::vector<std::shared_ptr<Entity>>> map_;
    std::list<std::shared_ptr<Entity>> squads_; //sorted by priority

    friend std::istream& operator>>(std::istream& is, Terrain& terrain);
    friend std::ostream& operator<<(std::ostream& os, const Terrain& terrain);
    friend class Summoner;
   
    int MAX_X;
    int MAX_Y;

    Terrain(const std::string& cfg_filename); //add
    void addSquad(Type id, Point); //called from summoner may be
    void live();

    std::shared_ptr<Summoner> getSummonerFirst() {
        int x = static_cast<int>(summoners_coords_.first.x);
        int y = static_cast<int>(summoners_coords_.first.y);
        return dynamic_pointer_cast<Summoner>(map_[y][x]);
    }

    std::shared_ptr<Summoner> getSummonerSecond() {
        int x = static_cast<int>(summoners_coords_.second.x);
        int y = static_cast<int>(summoners_coords_.second.y);
        return dynamic_pointer_cast<Summoner>(map_[y][x]);
    }
};

