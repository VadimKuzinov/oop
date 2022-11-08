#include "Summoner.h"


void Summoner::accumulateEnergy() {
    cur_energy_ = std::min(max_energy_, cur_energy_ + energy_regen_speed_);
}

void Summoner::summon() {
    auto distance = Point::distance(coords_, target_coords_);
    if (distance > summon_range_) {
        return;
    }

    if (summoned_school_ == "" || summoned_ability_ == "") {
        return;
    }

    auto ability = terrain_->getAcademy()[summoned_school_][summoned_ability_];
    if (ability.getEnergyCost() > cur_energy_) {
        return;
    }

    int cur_level = levels_of_schools_[summoned_school_];
    if (ability.getRequiredLevelOfSchool() > cur_level) {
        return;
    }

    cur_energy_ -= ability.getEnergyCost();
    terrain_->getAcademy()[summoned_school_][summoned_ability_].getModelWithLevel(cur_level);
    terrain_->addSquad(terrain_->getAcademy()[summoned_school_][summoned_ability_].getModelWithLevel(cur_level), target_coords_);
}

void Summoner::upgradeSchool() {
    if (summoned_school_ == "") {
        return;
    }

    auto school = terrain_->getAcademy()[summoned_school_];
    if (school.getRequiredXpForUpgrading() > xp_) {
        return;
    }

    ++levels_of_schools_[summoned_school_];
    xp_ -= school.getRequiredXpForUpgrading();
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

std::vector<std::pair<void (*)(std::shared_ptr<Entity>), const char*>> Summoner::getMenu() const {
    auto choices = Obstacle::getMenu();
    choices.push_back({[](std::shared_ptr<Entity> e){ return std::dynamic_pointer_cast<Summoner>(e)->tryToAccumulate(); }, "Accumulate"});
    choices.push_back({[](std::shared_ptr<Entity> e){ return std::dynamic_pointer_cast<Summoner>(e)->tryToSummon(); }, "Summon"});
    choices.push_back({[](std::shared_ptr<Entity> e){ return std::dynamic_pointer_cast<Summoner>(e)->tryToUpgrade(); }, "Upgrade"});
    return choices;
}

std::vector<std::pair<std::string, std::string>> Summoner::serialize() const {
    return serializeImpl(*this, properties_);
}

