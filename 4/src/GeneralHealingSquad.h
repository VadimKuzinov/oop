#pragma once
#include "GeneralSquad.h"
#include "IHealingSquad.h"
#include "Type.h"


class GeneralHealingSquad : public GeneralSquad, public IHealingSquad {
public:
    GeneralHealingSquad(Terrain*, Point coords, Type = GeneralHealing_);

    void heal() override;
    void act() override;
    void update() override;
};

