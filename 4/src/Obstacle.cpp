#include "Obstacle.h"


void Obstacle::receiveDamage(double value) {
    cur_hp_ -= value;
}

void Obstacle::setTargetCoords(Point target_coords) {
    target_coords_ = target_coords;
}

bool Obstacle::isAlive() const {
    return cur_hp_ > 0;
}

std::vector<std::pair<void (*)(std::shared_ptr<Entity>), const char*>> Obstacle::getMenu() const {
    return {};
}

std::vector<std::pair<std::string, std::string>> Obstacle::serialize() const {
    return serializeImpl(*this, properties_);
 }

