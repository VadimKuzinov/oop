#include "Academy.h"
#include "Utils.h"


std::istream& operator>>(std::istream& is, Ability& ability) {
    is >> ability.name_;
    is >> ability.energy_cost_;
    is >> ability.required_level_of_school_;
    is >> ability.model_;
    return is;
}

std::istream& operator>>(std::istream& is, School& school) {
    is >> school.name_;
    std::size_t qty;
    is >> qty;
    while (qty--) {
        Ability ability;
        is >> ability;
        school[ability.getName()] = std::move(ability);
    } 
    return is;
}

std::istream& operator>>(std::istream& is, Academy& academy) {
    std::size_t qty;
    is >> qty;
    while (qty--) {
        School school;
        is >> school;
        academy[school.getName()] = std::move(school);
    }
    return is;
}

School& Academy::operator[](const std::string& name) {
    return schools_[name];
}

Ability& School::operator[](const std::string& name) {
    return abilities_[name];
}

std::shared_ptr<Entity> Ability::getModel() const {
    return model_->clone();
}

