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
    double value = damage_;
    auto captured = getCaptured();
    captured->receiveDamage(value);
}

void MoralSquad::attack() {
    auto captured = getCaptured();
    if (captured == nullptr) {
        return;
    }

    auto distance = Point::distance(getCoords(), captured->getCoords());
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

std::vector<std::pair<void (*)(std::shared_ptr<Entity>), const char*>> MoralSquad::getMenu() const {
    auto choices = GeneralSquad::getMenu();
    return choices;
}

