#include "Obstacle.h"


void Obstacle::receiveDamage(double value) {
    cur_hp_ -= value;
}

bool Obstacle::isAlive() const {
    return cur_hp_ > 0;
}

std::vector<std::pair<void (*)(std::shared_ptr<Entity>), const char*>> Obstacle::getMenu() const {
    return {};
}
