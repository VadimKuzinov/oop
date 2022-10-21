#include "GeneralSquad.h"
#include "Type.h"
#include "Point.h"


GeneralSquad::GeneralSquad(const Terrain* terrain, Point coords, Type id) : Base(terrain, coords, id) {
}

GeneralSquad::update() {
    if (!captured_->isAlive()) {
        captured_ = nullptr;
    }

    if (captured_) {
        target_coords_ = captured_->coords_;
    }    
}

GeneralSquad::move() {
    auto vector_direction = Point::normalized(captured_->coords_ - coords_) * speed_;
    auto target_point = coords_ + vector_direction;
    auto int_target_point = Point::withIntCfs(target_point);
    int x = int_target_point.x;
    int y = int_target_point.y;
    if (terrain_->map_[y][x] != nullptr) {
        return;
    }

    coords_ = target_point;
}

GeneralSquad::giveDamage() {
    double value = damage_;
    captured_->receiveDamage(value);
}

GeneralSquad::attack() {
    auto distance = Point::distance(coords_, captured_->coords_);
    if (distance > attack_range_) {
        return;
    }

    giveDamage();
}

GeneralSquad::act() {
    update();

    if (moving_) {
        move();
    }

    if (attacking_) {
        attack();
    }
}

