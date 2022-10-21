#pragma once
#include "Base.h"
#include "IActive.h"
#include <memory>


class Summoner: public Base, public IActive {
protected:
    double summon_range_ = Summoner_Summon_Range_;
    double max_energy_ = Summoner_Energy_;
    double cur_energy_ = energy_limit_;
    double xp_ = 0;
    double energy_regen_speed_ = Summoner_Energy_Regen_Speed_;

    bool accumulating_ = true;
    bool summoning_ = false;
    bool upgrading_ = false;
    Type summoned_id_ = Obstacle_;

public:
    Summoner(Terrain* terrain, Point coords, Type = Summoner_);

    void summon();
    void accumulateEnergy();
    void upgradeSchool();
    void act() override;     
};

