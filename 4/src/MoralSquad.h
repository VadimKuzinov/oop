#pragma once
#include "GeneralSquad.h"
#include "Type.h"


class MoralSquad : public GeneralSquad {
protected:
    double morality_ = 0;
    double stabilization_speed_ = Moral_Stab_;

public:
    MoralSquad(Terrain*, Point coords, Type = Moral_);

    void stabilizeMorality();

    void act() override;
    void update() override;
    void attack() override;
    void giveDamage() override;
        
};

