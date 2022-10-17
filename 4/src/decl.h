#include <vector>
#include <list>

#include "BasicSquad.h"


enum Types {
    ImmoralSquad,
    GeneralSquad,
    ImmoralHealingSquad,
    GeneralHealingSquad,
    Summoner,
};


class ImmoralSquad: public BasicSquad {
protected:
    double damage_;
    double defense_;
    double loot_after_destr_;
};


class HealingProperty {
protected:
    double power_hp_add_;          
};


class ImmoralHealingSquad: public ImmoralSquad, public HealingProperty {  
};


class GeneralHealingSquad: public GeneralSquad, public HealingProperty {
};


class Summoner: public BasicSquad {
    double energy_;
    double xp_;
};


class Terrain {
    std::vector<std::vector<BasicSquad>> terrain_;

public:
    constexpr Terrain(std::size_t i_size_, std::size_t j_size_);
    constexpr std::vector<BasicSquad>& operator[](std::size_t it_);
};


class State {
    std::list<BasicSquad> srt_by_prior_;
   
};




