#pragma once
#include "Utils.h"
#include "Type.h"
#include "Obstacle.h"
#include "Point.h"
#include "Summoner.h"
#include <memory>


class GeneralSquad : public Obstacle {
protected:
    double damage_ = 4;
    double velocity_ = 0.014;
    int quantity_ = 1;
    double xp_for_destroying_ = 3;
    double attack_range_ = 2;

    bool moving_ = false;
    bool attacking_ = false;

    std::shared_ptr<Summoner> summoner_ = nullptr;

public:
    GeneralSquad(Terrain*, Point coords, Type = General_);
    virtual ~GeneralSquad() = default;

    void setSummoner(std::shared_ptr<Summoner> summoner) {
        summoner_ = summoner;
    }

    void tryToMove() {
        moving_ = true;
        attacking_ = false;
    }

    void tryToAttack() {
        moving_ = false;
        attacking_ = true;
    }

    std::vector<std::pair<void (*)(Entity*), const char*>> getMenu() const override;

    void act() override;
    virtual void update();
    virtual void move();
    virtual void attack();

    virtual void giveDamage();
    std::vector<std::pair<std::string, std::string>> serialize() const override;
};

