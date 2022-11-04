#pragma once
#include "GeneralSquad.h"
#include "Type.h"


class MoralSquad : virtual public GeneralSquad {
protected:
    double morality_ = 0;
    double stabilization_speed_ = Moral_Stab_;

public:
//    MoralSquad(Terrain*, Point coords, Type = Moral_);
    MoralSquad() = default;
    virtual ~MoralSquad() = default;

    std::vector<std::pair<void (*)(Entity*), const char*>> getMenu() const override;

    void stabilizeMorality();

    void act() override;
    void update() override;
    void attack() override;
    void giveDamage() override;
    std::vector<std::pair<std::string, std::string>> serialize() const override;
};

