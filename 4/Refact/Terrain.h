#pragma once
#include "Point.h"
#include "Type.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <memory>


class Summoner;
class Base;


class Terrain {
public:
    std::vector<std::vector<std::shared_ptr<Base>>> map_;
    std::list<std::shared_ptr<Base>> squads_; //sorted by priority

    friend std::istream& operator>>(std::istream& is, Terrain& terrain);
    friend std::ostream& operator<<(std::ostream& os, const Terrain& terrain);
    friend class Summoner;
   
    int MAX_X;
    int MAX_Y;

public:
    Terrain(const std::string& cfg_filename); //add

    void addSquad(Type id, Point); //called from summoner may be
    void live();
};


std::istream& operator>>(std::istream& is, Terrain& terrain);
std::ostream& operator<<(std::ostream& os, const Terrain& terrain);

