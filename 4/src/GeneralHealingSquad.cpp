#include "GeneralHealingSquad.h"


GeneralHealingSquad::GeneralHealingSquad(Terrain* terrain, Point coords, Type id) : GeneralSquad(terrain, coords, id) {
}

void GeneralHealingSquad::heal() {
    cur_hp_ = std::max(max_hp_, cur_hp_ + healing_speed_);
}

void GeneralHealingSquad::update() {
    GeneralSquad::update();
}

void GeneralHealingSquad::act() {
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

