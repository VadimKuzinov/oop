#pragma once
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

    constexpr static auto properties_ = std::tuple_cat(Obstacle::properties_, 
                                        std::make_tuple(std::make_pair(&GeneralSquad::damage_, "damage"),
                                                        std::make_pair(&GeneralSquad::velocity_, "velocity"),
                                                        std::make_pair(&GeneralSquad::quantity_, "quantity"),
                                                        std::make_pair(&GeneralSquad::xp_for_destroying_, "xp_for_destroying"),
                                                        std::make_pair(&GeneralSquad::attack_range_, "attack_range")));

    void set(const std::string& name, const std::string& value) override {
        return setImpl(*this, properties_, name, value, std::make_index_sequence<std::tuple_size_v<decltype(properties_)>>{});
    }

public:
//    GeneralSquad(Terrain*, Pint coords, Type = General_);
    GeneralSquad() = default;
    virtual ~GeneralSquad() = default;
    GeneralSquad(const GeneralSquad&) = default;

    std::shared_ptr<Entity> clone() const {
        return std::shared_ptr<Entity>(new GeneralSquad(*this));
    }

    void setSummoner(std::shared_ptr<Summoner> summoner) {
        summoner_ = summoner;
    }

    void setQuantity(int quantity) {
        quantity_ = quantity;
    }

    void tryToMove() {
        moving_ = true;
        attacking_ = false;
    }

    void tryToAttack() {
        moving_ = false;
        attacking_ = true;
    }

    std::vector<std::pair<void (*)(std::shared_ptr<Entity>), const char*>> getMenu() const override;

    void act() override;
    virtual void update();
    virtual void move();
    virtual void attack();

    virtual void giveDamage();
    std::vector<std::pair<std::string, std::string>> serialize() const override;
};

