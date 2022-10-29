#pragma once
#include "Utils.h"
#include "Type.h"
#include "Obstacle.h"
#include "Point.h"
#include "IActive.h"
#include "Summoner.h"
#include <memory>


class GeneralSquad : public Obstacle, public IActive {
protected:
    double damage_;
    double velocity_;
    int quantity_;
    double xp_for_destroying_;
    double attack_range_;

    bool moving_ = false;
    bool attacking_ = false;

    std::shared_ptr<Summoner> summoner_ = nullptr;

    std::shared_ptr<Entity> captured_ = nullptr;
    Point target_coords_;

public:
    GeneralSquad(Terrain*, Point coords, Type = General_);
    virtual ~GeneralSquad() = default;

    void setSummoner(std::shared_ptr<Summoner> summoner) {
        summoner_ = summoner;
    }

    void tryToMove() {
        moving_ = true;
    }

    void tryToAttack() {
        attacking_ = true;
    }

    void setCaptured(std::shared_ptr<Obstacle> captured) {
        captured_ = captured;
    }   

    std::vector<std::pair<void (*)(Entity*), const char*>> getMenu() const override {
        return Game::menu(this);
    }   

    void setTargetCoords(Point target_coords) {
        std::cout << "Trying to set target coords for " << id_ << std::endl;
        std::cout << target_coords << std::endl;
        auto int_p = Point::withIntCfs(target_coords);
        if (int_p.y >= terrain_->MAX_Y || int_p.x >= terrain_->MAX_X) {
            return;
        }

        target_coords_ = target_coords;
        auto cell = terrain_->map_[static_cast<int>(int_p.y)][static_cast<int>(int_p.x)];
        if (cell != nullptr) {
            captured_ = cell;
        }
        std::cout << "captured is set" << std::endl;
    }   

    void act() override;
    virtual void update();
    virtual void move();
    virtual void attack();

    virtual void giveDamage();

};

