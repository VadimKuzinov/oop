#include "GeneralSquad.h"
#include "Type.h"
#include "Point.h"
#include <iostream>


GeneralSquad::GeneralSquad(Terrain* terrain, Point coords, Type id) : Obstacle(terrain, coords, id) {
}

void GeneralSquad::update() {
    if (captured_ && !captured_->isAlive()) {
        captured_ = nullptr;
    }

    if (captured_) {
        target_coords_ = captured_->getCoords();
    }    
}

void GeneralSquad::move() {
    std::cout << "CURRENT COORDS: " << coords_ << '\n';
    std::cout << "TARGET COORDS: " << target_coords_ << '\n';
    double act_velocity = std::min(Point::distance(coords_, target_coords_), velocity_);
    std::cout << "Vector dif: " << target_coords_ - coords_ << '\n';
    std::cout << "Actual velocity: " << act_velocity << '\n';
    auto vector_direction = Point::normalized(target_coords_ - coords_) * act_velocity;
    std::cout << "VECTOR DIRECTION: " << vector_direction << '\n';
    auto target_point = coords_ + vector_direction;
    std::cout << "TARGET POINT: " << target_point << '\n';
    auto int_target_point = Point::withIntCfs(target_point);
    std::cout << "INT TARGET POINT: " << int_target_point << '\n';
    int x = int_target_point.x;
    int y = int_target_point.y;
    if (terrain_->map_[y][x] != nullptr && terrain_->map_[y][x].get() != this) {
        std::cout << "RETURNED!!!" << '\n';
        moving_ = false;
        return;
    }

    Point cur_int_coords_ = Point::withIntCfs(coords_);
    coords_ = target_point;
    if (int_target_point == cur_int_coords_) {
        return;
    }
    terrain_->map_[y][x] = terrain_->map_[cur_int_coords_.y][cur_int_coords_.x];
    terrain_->map_[cur_int_coords_.y][cur_int_coords_.x] = nullptr;
    std::cout << "NOW: " << y << ' ' << x << " is occuppied by us and " << cur_int_coords_.y << ' ' << cur_int_coords_.x << " is nullptr\n";
    std::cout << "New coords: " << coords_ << '\n';
}

void GeneralSquad::giveDamage() {
    double value = damage_;
    captured_->receiveDamage(value);
}

void GeneralSquad::attack() {
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
    choices.push_back({[](Entity* e){ return dynamic_cast<GeneralSquad*>(e)->tryToMove(); }, "Attack"});
    return choices;
}   

 
