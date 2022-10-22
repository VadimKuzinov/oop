#pragma once
#include "Type.h"
#include "IHealingSquad.h"
#include "MoralSquad.h"


class MoralHealingSquad : public MoralSquad, public IHealingSquad {
public:
    MoralHealingSquad(Terrain*, Point coords, Type = MoralHealing_);

    void heal() override;
    void act() override;
    void update() override;
};

