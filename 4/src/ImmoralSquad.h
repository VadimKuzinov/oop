#pragma once
#include "BasicSquad.h"


class ImmoralSquad: public BasicSquad {
protected:
    double damage_;
    double defense_;
    double loot_after_destr_;

public:    
    ImmoralSquad(enum Types type = Types::_ImmoralSquad);
    virtual ~ImmoralSquad() = default;
};

