#pragma once
#include "Type.h"
#include "MoralSquad.h"
#include "GeneralHealingSquad.h"


class MoralHealingSquad : public MoralSquad, public GeneralHealingSquad {
public:
    MoralHealingSquad(Terrain*, Point coords, Type = MoralHealing_);
    virtual ~MoralHealingSquad() = default;

    void act() override;
    void heal() override;
    void update() override;
};

