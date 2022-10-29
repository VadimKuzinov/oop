#pragma once
#include "GeneralSquad.h"
#include "Type.h"


class MoralSquad : virtual public GeneralSquad {
protected:
    double morality_ = 0;
    double stabilization_speed_ = Moral_Stab_;

public:
    MoralSquad(Terrain*, Point coords, Type = Moral_);
    virtual ~MoralSquad() = default;
   
    std::vector<std::pair<void (*)(Entity*), const char*>> getMenu() const override {
        return Game::menu(this);
    }

    void stabilizeMorality();

    void act() override;
    void update() override;
    void attack() override;
    void giveDamage() override;        
};

