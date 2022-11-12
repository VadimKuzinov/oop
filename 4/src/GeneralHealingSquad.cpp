#include "GeneralHealingSquad.h"


void GeneralHealingSquad::heal() {
    cur_hp_ = std::min(max_hp_, cur_hp_ + healing_speed_);
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
  
std::vector<std::pair<void (*)(std::shared_ptr<Entity>), const char*>> GeneralHealingSquad::getMenu() const {
    auto choices = GeneralSquad::getMenu();
    choices.push_back({[](std::shared_ptr<Entity> e){ return std::dynamic_pointer_cast<GeneralHealingSquad>(e)->tryToHeal(); }, "Heal"});
    return choices;
}

