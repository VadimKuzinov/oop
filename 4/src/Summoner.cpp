#include "Summoner.h"

/*
Summoner::Summoner(Terrain* terrain, Point coords, Type id) : Obstacle(terrain, coords, id) {
}
*/
void Summoner::accumulateEnergy() {
    cur_energy_ = std::min(max_energy_, cur_energy_ + energy_regen_speed_);
}

void Summoner::summon() {
    if (summoned_school_ == nullptr) {
        return;
    }

    auto distance = Point::distance(coords_, target_coords_);
    if (distance > summon_range_) {
        return;
    }

    terrain_->addSquad(summoned_school_, target_coords_);
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

std::vector<std::pair<std::string, std::string>> Summoner::serialize() const {
    auto res = Obstacle::serialize();
    res.push_back(std::make_pair("summon_range", std::to_string(summon_range_)));
    res.push_back(std::make_pair("max_energy", std::to_string(max_energy_)));
    res.push_back(std::make_pair("cur_energy", std::to_string(cur_energy_)));
    res.push_back(std::make_pair("xp", std::to_string(xp_)));
    res.push_back(std::make_pair("en_reg_speed", std::to_string(energy_regen_speed_)));
    return res;
}

