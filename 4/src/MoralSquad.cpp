#include "MoralSquad.h"
#include <iostream>


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
    double value = getDamage();
    auto captured = getCaptured();
    captured->receiveDamage(value);
    if (!captured->isAlive()) {
        std::static_pointer_cast<Summoner>(getSummoner())->receiveXp(std::static_pointer_cast<GeneralSquad>(captured)->getXpForDestroying());
    }
}

void MoralSquad::attack() {
    auto captured = getCaptured();
    if (captured == nullptr) {
        return;
    }

    auto distance = Point::distance(getCoords(), captured->getCoords());
    if (distance > getAttackRange()) {
        return;
    }

    giveDamage();
}

void MoralSquad::act() {
    update();

    if (isMoving()) {
        move();
    }

    if (isAttacking()) {
        attack();
    }
}

