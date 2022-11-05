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
    std::vector<std::pair<std::string, std::string>> res;
    res.push_back(std::make_pair("coords", std::string(coords_)));
    res.push_back(std::make_pair("max_hp", std::to_string(max_hp_)));
    res.push_back(std::make_pair("cur_hp", std::to_string(cur_hp_)));
    res.push_back(std::make_pair("trg_coords", std::string(target_coords_)));
    return res;
}

