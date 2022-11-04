#pragma once
#include "Point.h"
#include "Type.h"
#include "Academy.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <memory>
#include <typeinfo>


class Terrain;
class Summoner;
class Entity;
class School;

std::istream& operator>>(std::istream& is, Terrain& terrain);
std::ostream& operator<<(std::ostream& os, const Terrain& terrain);


class Terrain {
private:
    std::pair<std::shared_ptr<Summoner>, std::shared_ptr<Summoner>> summoners_;
    std::pair<Point, Point> summoners_coords_;
    std::vector<std::vector<std::shared_ptr<Entity>>> map_;
    std::list<std::shared_ptr<Entity>> squads_; //sorted by priority
    Academy academy_;
    friend std::istream& operator>>(std::istream& is, Terrain& terrain);
   
    int MAX_X;
    int MAX_Y;

public:
    Terrain(const std::string& academy_cfg, const std::string& map_cfg);
    void addSquad(const std::string&, const std::string&, Point); //called from summoner may be
    void live();

    std::shared_ptr<Summoner> getSummonerFirst() {
        int x = static_cast<int>(summoners_coords_.first.x);
        int y = static_cast<int>(summoners_coords_.first.y);
        return std::dynamic_pointer_cast<Summoner>(map_[y][x]);
    }

    std::shared_ptr<Summoner> getSummonerSecond() {
        int x = static_cast<int>(summoners_coords_.second.x);
        int y = static_cast<int>(summoners_coords_.second.y);
        return std::dynamic_pointer_cast<Summoner>(map_[y][x]);
    }

    const Academy& getAcademy() const {
        return academy_;
    }

    void clearCorpses();
};

