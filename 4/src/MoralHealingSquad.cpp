#include "MoralHealingSquad.h"


void MoralHealingSquad::heal() {
    cur_hp_ = std::max(max_hp_, cur_hp_ + healing_speed_);
}

void MoralHealingSquad::update() {
    MoralSquad::update();
}

void MoralHealingSquad::act() {
    update();

    if (moving_) {
        move();
    }

    if (attacking_) {
        attack();
    }

    if (healing_) {
        heal();
    }
}

std::vector<std::pair<void (*)(Entity*), const char*>> MoralHealingSquad::getMenu() const {
    auto choices = GeneralHealingSquad::getMenu();
    return choices;
}

std::vector<std::pair<std::string, std::string>> MoralHealingSquad::serialize() const {
    auto res = GeneralHealingSquad::serialize();
    res.push_back(std::make_pair("morality", std::to_string(morality_)));
    res.push_back(std::make_pair("stab_speed", std::to_string(stabilization_speed_)));
    return res;
}

