#include "MoralHealingSquad.h"


MoralHealingSquad::MoralHealingSquad(Terrain* terrain, Point coords, Type id) : MoralSquad(terrain, coords, id) {
}

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

