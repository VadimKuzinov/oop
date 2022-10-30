#include "Summoner.h"


Summoner::Summoner(Terrain* terrain, Point coords, Type id) : Obstacle(terrain, coords, id) {
}

void Summoner::accumulateEnergy() {
    cur_energy_ = std::max(max_energy_, cur_energy_ + energy_regen_speed_);
}

void Summoner::summon() {
    std::cout << "TRYING TO SUMMON: " << summoned_id_ << '\n';
    if (summoned_id_ == Obstacle_) {
        return;
    }

    std::cout << "Target coords: " << target_coords_ << '\n';

    auto distance = Point::distance(coords_, target_coords_);
    std::cout << "Distance : " << distance << '\n';
    if (distance > summon_range_) {
        return;
    }

    if (terrain_->map_[target_coords_.y][target_coords_.x] != nullptr) {
        return;
    }

    terrain_->addSquad(summoned_id_, target_coords_);
}

void Summoner::upgradeSchool() {
    return;
}

void Summoner::act() {
    if (accumulating_) {
        accumulateEnergy();
        return;
    }

    if (summoning_) {
        summon();
        summoning_ = false;
        return;
    }

    if (upgrading_) {
        upgradeSchool();
        upgrading_ = false;
        return;
    }
}

std::vector<std::pair<void (*)(Entity*), const char*>> Summoner::getMenu() const {
    auto choices = Obstacle::getMenu();
    choices.push_back({[](Entity* e){ return dynamic_cast<Summoner*>(e)->tryToAccumulate(); }, "Accumulate"});
    choices.push_back({[](Entity* e){ return dynamic_cast<Summoner*>(e)->tryToSummon(); }, "Summon"});
    choices.push_back({[](Entity* e){ return dynamic_cast<Summoner*>(e)->tryToUpgrade(); }, "Upgrade"});
    return choices;
}
 
