#pragma once
#include "Type.h"
#include "MoralSquad.h"
#include "GeneralHealingSquad.h"


class MoralHealingSquad : public MoralSquad, public GeneralHealingSquad {
public:
    MoralHealingSquad(Terrain*, Point coords, Type = MoralHealing_);
    virtual ~MoralHealingSquad() = default;

    std::vector<std::pair<void (*)(Entity*), const char*>> getMenu() const override;

    void act() override;
    void heal() override;
    void update() override;

    std::vector<std::pair<std::string, std::string>> serialize() const override;
};

