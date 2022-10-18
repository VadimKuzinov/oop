#pragma once
#include "BasicSquad.h"


class ImmoralSquad: public BasicSquad {
protected:
    double damage_;
    double defense_;
    double loot_after_destr_;

public:    
    ImmoralSquad(Terrain*, enum Types = Types::_ImmoralSquad);
    virtual ~ImmoralSquad() = default;
};

