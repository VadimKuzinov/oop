#include "MoralSquad.h"


MoralSquad::MoralSquad(Terrain* terrain, Point coords, Type id) : GeneralSquad(terrain, coords, id) {
}

void MoralSquad::stabilizeMorality() {
    if (morality_ < 0) {
        morality_ += stabilization_speed_;
    }
    else {
        morality_ -= stabilization_speed_;
    }

    if (morality_ >= -stabilization_speed_ && morality_ <= stabilization_speed_) {
        morality_ = 0;
    }
}

void MoralSquad::update() {
    GeneralSquad::update();
    
    stabilizeMorality();
}

void MoralSquad::giveDamage() {
    double value = damage_;
    captured_->receiveDamage(value);
}

void MoralSquad::attack() {
    auto distance = Point::distance(coords_, captured_->getCoords());
    if (distance > attack_range_) {
        return;
    }

    giveDamage();
}

void MoralSquad::act() {
    update();

    if (moving_) {
        move();
    }

    if (attacking_) {
        attack();
    }
}

std::vector<std::pair<void (*)(Entity*), const char*>> MoralSquad::getMenu() const {
    auto choices = GeneralSquad::getMenu();
    return choices;
}

std::vector<std::pair<std::string, std::string>> MoralSquad::serialize() const {
    auto res = GeneralSquad::serialize();
    res.push_back(std::make_pair("morality", std::to_string(morality_)));
    res.push_back(std::make_pair("stab_speed", std::to_string(stabilization_speed_)));
    return res;
}

