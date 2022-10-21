#include "Summoner.h"


Summoner::Summoner(Terrain* terrain, Point coords, Type id) : Base(terrain, coords, id) {
}

void Summoner::accumulateEnergy() {
    cur_energy_ = std::max(max_energy_, cur_energy + energy_regen_speed_);
}

void Summoner::summon() {
    if (summoned_id_ == Obstacle_) {
        return;
    }

    auto distance = Point::distance(coords_, target_coords_);
    if (distance > summon_range_) {
        return;
    }

    if (terrain_->map_[target_coords_.y][target_coords_.x] != nullptr) {
        return;
    }

    terrain_->addSquad(summoned_id_, target_coords_);
}

void Summoner::act() {
    if (accumulating_) {
        accumulateEnergy();
        return;
    }

    if (summoning_) {
        summon();
        return;
    }

    if (upgrading_) {
        upgradeSchool();
        return;
    }
}

