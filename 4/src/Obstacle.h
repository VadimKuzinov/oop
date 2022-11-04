#pragma once
//#include "Utils.h"
#include "Entity.h"
#include "Type.h"
#include "Point.h"
//#include "Terrain.h"
#include <memory>


class Terrain;

class Obstacle : public Entity {
protected:
//    Type id_;

    Terrain* terrain_;
    Point coords_;
    double max_hp_ = Obstacle_Mhp_;
    double cur_hp_ = max_hp_;
    int priority_ = Obstacle_Pr_;
    
    std::shared_ptr<Entity> captured_ = nullptr;
    Point target_coords_;

public:
    Obstacle() = default;
    virtual ~Obstacle() = default;

    void setTerrain(Terrain* terrain) {
        terrain_ = terrain;
    }

    void setCoords(Point where) {
        coords_ = where;
    }

    void setCaptured(std::shared_ptr<Entity> captured) {
        captured_ = captured;
    }
    
    void setTargetCoords(Point target_coords);
    void setDefaults();
    void receiveDamage(double) override;

    double getMaxHp() const {
        return max_hp_;
    }

    std::vector<std::pair<void (*)(Entity*), const char*>> getMenu() const override;

    void act() override {
    }

    bool isAlive() const override;

    int getPriority() const override {
        return priority_;
    }
/*
    Type getId() const override {
        return id_;
    }
*/
    Point getCoords() const override {
        return coords_;
    }

    double getCurHp() const {
        return cur_hp_;
    }

    void killMySelf() override {
        cur_hp_ = 0;
    }
    
    std::vector<std::pair<std::string, std::string>> serialize() const override;
};

