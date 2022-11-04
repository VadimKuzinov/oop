#include "GeneralSquad.h"
#include "Type.h"
#include "Point.h"
#include <iostream>


void GeneralSquad::update() {
    if (captured_ && !captured_->isAlive()) {
        captured_ = nullptr;
    }

    if (captured_) {
        target_coords_ = captured_->getCoords();
    }    
}

void GeneralSquad::move() {
    double act_velocity = std::min(Point::distance(coords_, target_coords_), velocity_);
    auto vector_direction = Point::normalized(target_coords_ - coords_) * act_velocity;
    auto target_point = coords_ + vector_direction;
    auto int_target_point = Point::withIntCfs(target_point);
    if (terrain_->getMap()[int_target_point] != nullptr && terrain_->getMap()[int_target_point].get() != this) {
        moving_ = false;
        return;
    }

    Point cur_int_coords_ = Point::withIntCfs(coords_);
    coords_ = target_point;

    if (int_target_point == cur_int_coords_) {
        if (cur_int_coords_ == target_coords_) {
            moving_ = false;
        }
        return;
    }
    terrain_->getMap()[int_target_point] = terrain_->getMap()[cur_int_coords_];
    terrain_->getMap()[cur_int_coords_] = nullptr;
}

void GeneralSquad::giveDamage() {
    double value = damage_;
    captured_->receiveDamage(value);
}

void GeneralSquad::attack() {
    if (captured_ == nullptr) {
        return;
    }

    auto distance = Point::distance(coords_, captured_->getCoords());
    if (distance > attack_range_) {
        return;
    }

    giveDamage();
}

void GeneralSquad::act() {
    update();
    if (moving_) {
        move();
    }

    if (attacking_) {
        attack();
    }
}

std::vector<std::pair<void (*)(Entity*), const char*>> GeneralSquad::getMenu() const {
    auto choices = Obstacle::getMenu();
    choices.push_back({[](Entity* e){ return dynamic_cast<GeneralSquad*>(e)->tryToMove(); }, "Move"});
    choices.push_back({[](Entity* e){ return dynamic_cast<GeneralSquad*>(e)->tryToAttack(); }, "Attack"});
    return choices;
}   

std::vector<std::pair<std::string, std::string>> GeneralSquad::serialize() const {
    auto res = Obstacle::serialize();
    res.push_back(std::make_pair("damage", std::to_string(damage_)));
    res.push_back(std::make_pair("velocity", std::to_string(velocity_)));
    res.push_back(std::make_pair("qty", std::to_string(quantity_)));
    res.push_back(std::make_pair("xp_for_dsrt", std::to_string(xp_for_destroying_)));
    res.push_back(std::make_pair("attack_range", std::to_string(attack_range_)));
    return res;
} 

