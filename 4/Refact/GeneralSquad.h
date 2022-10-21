#pragma once
#include "Type.h"
#include "Base.h"
#include "Point.h"
#include "IActive.h"
#include <memory>


class GeneralSquad : public Base, public IActive {
protected:
    double damage_;
    double velocity_;
    int quantity_;
    double xp_for_destroying_;
    double attack_range_;

    bool moving_ = false;
    bool attacking_ = false;

    std::shared_ptr<Summoner> summoner_ = nullptr;


public:
    GeneralSquad(const Terrain*, Point coords, Type = General_);

    void setSummoner(std::shared_ptr<Summoner> summoner) {
        summoner_ = summoner;
    }

    void setCaptured(std::shared_ptr<Base> captured) {
        captured_ = captured;
    }

    void setTargetCoords(Point target_coords) {
        target_coords_ = target_coords;
    }

    void tryToMove() {
        moving_ = true;
    }

    void tryToAttack() {
        attacking_ = true;
    }

    void act() override;
    virtual void update();
    virtual void move();
    virtual void attack();

    virtual void giveDamage();

};

