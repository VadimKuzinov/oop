#pragma once
#include "Terrain.h"
#include "Type.h"
#include "Obstacle.h"
#include <memory>
#include <string>


class Summoner: public Obstacle {
protected:
    double summon_range_ = Summoner_Summon_Range_;
    double max_energy_ = Summoner_Energy_;
    double cur_energy_ = max_energy_;
    double xp_ = 0;
    double energy_regen_speed_ = Summoner_Energy_Regen_Speed_;

    bool accumulating_ = true;
    bool summoning_ = false;
    bool upgrading_ = false;

    std::string summoned_school_;
    std::string summoned_ability_;

    constexpr static auto properties_ = std::tuple_cat(Obstacle::properties_, 
                                        std::make_tuple(std::make_pair(&Summoner::summon_range_, "summon_range"),
                                                        std::make_pair(&Summoner::max_energy_, "max_energy"),
                                                        std::make_pair(&Summoner::cur_energy_, "cur_energy"),
                                                        std::make_pair(&Summoner::xp_, "xp"),
                                                        std::make_pair(&Summoner::energy_regen_speed_, "energy_regen_speed")));

    void set(const std::string& name, const std::string& value) override {
        return setImpl(*this, properties_, name, value, std::make_index_sequence<std::tuple_size_v<decltype(properties_)>>{});
    }

public:
    //Summoner(Terrain* terrain, Point coords, Type = Summoner_);
    Summoner() = default;
    ~Summoner() = default;
    Summoner(const Summoner&) = default;

    std::shared_ptr<Entity> clone() const {
        return std::shared_ptr<Entity>(new Summoner(*this));
    }  

    void tryToAccumulate() {
        accumulating_ = true; summoning_ = false; upgrading_ = false;
    }

    void tryToSummon() {
        summoning_ = true; accumulating_ = false; upgrading_ = false;
    }

    void tryToUpgrade() {
        summoning_ = false; accumulating_ = false; upgrading_ = true; 
    }

    Terrain* getTerrain() const {
        return terrain_;
    }

    void setSummonedSchool(const std::string& summoned_school) {
        summoned_school_ = summoned_school;
    }

    void setSummonedAbility(const std::string& summoned_ability) {
        summoned_ability_ = summoned_ability;
    }

    std::vector<std::pair<void (*)(Entity*), const char*>> getMenu() const override;
    std::vector<std::pair<std::string, std::string>> serialize() const override;

    void summon();
    void accumulateEnergy();
    void upgradeSchool();
    void act() override;
};

