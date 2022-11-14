#include "MoralHealingSquad.h"


void MoralHealingSquad::heal() {
    auto cur_hp = getCurHp();
    auto max_hp = getMaxHp();
    setCurHp(std::min(max_hp, cur_hp + healing_speed_));
}

void MoralHealingSquad::update() {
    MoralSquad::update();
}

void MoralHealingSquad::act() {
    update();

    if (isMoving()) {
        move();
    }

    if (isAttacking()) {
        attack();
    }

    if (isHealing()) {
        heal();
    }
}

