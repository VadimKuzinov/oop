#pragma once
#include "Type.h"
#include "Point.h"
#include "Terrain.h"


class Base {
protected:
    Type id_;

    Terrain* terrain_;
    Point coords_;
    double max_hp_ = Obstacle_Mhp_;
    double cur_hp_ = max_hp_;
    int priority_ = Obstacle_Pr_;

public:
    Base(const Terrain*, Point coords, Type = Obstacle_);
    void setDefaults();

    virtual void act() {
    }

    virtual void receiveDamage(double);
    bool isAlive() const;
};
