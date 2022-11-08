#include "MoralHealingSquad.h"


void MoralHealingSquad::heal() {
    cur_hp_ = std::min(max_hp_, cur_hp_ + healing_speed_);
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

std::vector<std::pair<void (*)(std::shared_ptr<Entity>), const char*>> MoralHealingSquad::getMenu() const {
    auto choices = GeneralHealingSquad::getMenu();
    return choices;
}

std::vector<std::pair<std::string, std::string>> MoralHealingSquad::serialize() const {
    return serializeImpl(*this, properties_);
}

