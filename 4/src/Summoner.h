#pragma once
#include "Terrain.h"
#include "Type.h"
#include "Entity.h"
#include "IActive.h"
#include <memory>


class Summoner: public Obstacle, public IActive {
protected:
    double summon_range_ = Summoner_Summon_Range_;
    double max_energy_ = Summoner_Energy_;
    double cur_energy_ = max_energy_;
    double xp_ = 0;
    double energy_regen_speed_ = Summoner_Energy_Regen_Speed_;

    bool accumulating_ = true;
    bool summoning_ = false;
    bool upgrading_ = false;
    Type summoned_id_ = Obstacle_;

public:
    Summoner(Terrain* terrain, Point coords, Type = Summoner_);
    ~Summoner() = default;
  
    std::vector<std::pair<void (*)(Entity*), const char*>> getMenu() const override {
        auto choices = Obstacle::getMenu();
        choices.push_back([](Entity* squad){ 
    }

    void tryToAccumulate() {
        accumulating_ = true;
        summoning_ = false;
        upgrading_ = false;
    }

    void tryToSummon() {
        summoning_ = true;
        accumulating_ = false;
        upgrading_ = false;
    }

    void tryToUpgrade() {
        summoning_ = false;
        accumulating_ = false;
        upgrading_ = true; 
    }

    void setSummonedId(Type id) {
        summoned_id_ = id;
    }

    Terrain* getTerrain() const {
        return terrain_;
    }

    void summon();
    void accumulateEnergy();
    void upgradeSchool();
    void act() override;
};

