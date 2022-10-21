#pragma once
#include "Type.h"


class IHealingSquad {
protected:
    double healing_speed_ = Healing_Speed_;
    bool healing_ = false;

public:
    virtual void heal() = 0;
};

