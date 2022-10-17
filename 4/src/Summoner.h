#pragma once
#include "BasicSquad.h"


class Summoner: public BasicSquad {
protected:
    double energy_;
    double xp_;

public:
    Summoner(enum Types type = Types::_Summoner); 
    virtual ~Summoner() = default;
};

