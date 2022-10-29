#pragma once
#include "Type.h"
#include "Point.h"


class Terrain;

class Base {
protected:
    Type id_;

    Terrain* terrain_;
    Point coords_;
    double max_hp_ = Obstacle_Mhp_;
    double cur_hp_ = max_hp_;
    int priority_ = Obstacle_Pr_;

public:
    Base(Terrain*, Point coords, Type = Obstacle_);
    virtual ~Base() = default;

    void setDefaults();
    virtual void receiveDamage(double);

    virtual void act() {
    }

    bool isAlive() const;

    int getPriority() const {
        return priority_;
    }

    Type getId() const {
        return id_;
    }

    Point getCoords() const {
        return coords_;
    }
};
