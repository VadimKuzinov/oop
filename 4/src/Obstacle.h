#pragma once
#include "Utils.h"
#include "Entity.h"
#include "Type.h"
#include "Point.h"


class Terrain;

class Obstacle : public Entity {
protected:
    Type id_;

    Terrain* terrain_;
    Point coords_;
    double max_hp_ = Obstacle_Mhp_;
    double cur_hp_ = max_hp_;
    int priority_ = Obstacle_Pr_;

public:
    Obstacle(Terrain*, Point coords, Type = Obstacle_);
    virtual ~Obstacle() = default;

    void setDefaults();
    void receiveDamage(double) override;

    std::vector<std::pair<void (*)(Entity*), const char*>> getMenu() const override;

    void act() override {
    }

    bool isAlive() const override;

    int getPriority() const override {
        return priority_;
    }

    Type getId() const override {
        return id_;
    }

    Point getCoords() const override {
        return coords_;
    }

    double getCurHp() const {
        return cur_hp_;
    }

    void killMySelf() override {
        cur_hp_ = 0;
    }
};
