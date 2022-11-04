#pragma once
#include "Point.h"
#include "Type.h"
#include "Map.h"
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

class Terrain {
private:
    std::pair<std::shared_ptr<Summoner>, std::shared_ptr<Summoner>> summoners_;
    Map map_;
    Academy academy_;
    friend std::istream& operator>>(std::istream& is, Terrain& terrain);

    void addSummoner(std::shared_ptr<Entity>);

public:
    Terrain(const std::string& academy_cfg, const std::string& map_cfg);
    void addSquad(const std::string&, const std::string&, Point);
    void live();

    std::shared_ptr<Summoner> getSummonerFirst() {
        return summoners_.first;
    }

    std::shared_ptr<Summoner> getSummonerSecond() {
        return summoners_.second;
    }

    const Academy& getAcademy() const {
        return academy_;
    }

    Map& getMap() {
        return map_;
    }
};

