#include "Summoner.h"


void Summoner::accumulateEnergy() {
    cur_energy_ = std::min(max_energy_, cur_energy_ + energy_regen_speed_);
}

void Summoner::summon() {
    auto coords = getCoords();
    auto target_coords = getTargetCoords();
    auto terrain = getTerrain();

    auto distance = Point::distance(coords, target_coords);
    if (distance > summon_range_) {
        return;
    }

    if (summoned_school_ == "" || summoned_ability_ == "") {
        return;
    }

    auto ability = terrain->getAcademy()[summoned_school_][summoned_ability_];
    if (ability.getEnergyCost() > cur_energy_) {
        return;
    }

    int cur_level = levels_of_schools_[summoned_school_];
    if (ability.getRequiredLevelOfSchool() > cur_level) {
        return;
    }

    cur_energy_ -= ability.getEnergyCost();
    terrain->getAcademy()[summoned_school_][summoned_ability_].getModelWithLevel(cur_level);
    terrain->addSquad(terrain->getAcademy()[summoned_school_][summoned_ability_].getModelWithLevel(cur_level), target_coords, std::static_pointer_cast<Summoner>(shared_from_this()));
}

void Summoner::upgradeSchool() {
    auto terrain = getTerrain();

    if (summoned_school_ == "") {
        return;
    }

    auto school = terrain->getAcademy()[summoned_school_];
    if (school.getRequiredXpForUpgrading() > xp_) {
        return;
    }

    ++levels_of_schools_[summoned_school_];
    xp_ -= school.getRequiredXpForUpgrading();
}

void Summoner::act() {
    if (isAccumulating()) {
        accumulateEnergy();
        return;
    }

    if (isSummoning()) {
        summon();
        summoning_ = false;
        return;
    }

    if (isUpgrading()) {
        upgradeSchool();
        upgrading_ = false;
        return;
    }
}

