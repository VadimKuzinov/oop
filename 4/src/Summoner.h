#pragma once
#include "BasicSquad.h"


class Summoner: public BasicSquad {
protected:
    double energy_;
    double xp_;

public:
    Summoner(Terrain* terrain, enum Types = Types::_Summoner); 
    virtual ~Summoner() = default;
};

