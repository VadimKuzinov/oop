#pragma once
#include "BasicSquad.h"


class Summoner: public BasicSquad {
protected:
    double radius_;
    double energy_;
    double energy_limit_;
    double xp_ = 0;
    double energy_regen_add_;

public:
    Summoner(Terrain* terrain, enum Types = _Summoner); 
    virtual ~Summoner() = default;

    void SetRadius(double r);
    void Summon(enum Types, const Point& where);
};

