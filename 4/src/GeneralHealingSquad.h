#pragma once
#include "GeneralSquad.h"
#include "Type.h"


class GeneralHealingSquad : virtual public GeneralSquad {
protected:
    double healing_speed_ = Healing_Speed_;
    bool healing_ = false;

public:
    GeneralHealingSquad(Terrain*, Point coords, Type = GeneralHealing_);
    virtual ~GeneralHealingSquad() = default;    

    void tryToHeal() {
        healing_ = true;
    }

    virtual void heal();
    void act() override;
    void update() override;
};

