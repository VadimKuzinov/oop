#include "BasicSquad.h"
#include <cmath>


BasicSquad::BasicSquad(Terrain* terrain, enum Types type): terrain_(terrain), id(type) {
}

void BasicSquad::SetCoords(const Point& p) {
    coords = p;
}

void BasicSquad::SetPriority(std::size_t priority) {
    priority_ = priority;
}

void BasicSquad::SetPopulation(std::size_t population) {
    population_ = population;
}

void BasicSquad::SetSpeed(double speed) {
    speed_ = speed;
}

void BasicSquad::SetMaxHp(double max_hp) {
    max_hp_ = max_hp;
}

void BasicSquad::SetAttackRange(double attack_range) {
    attack_range_ = attack_range;
}

void BasicSquad::TryToAttack() {
    attacking_ = true;
    moving_ = false;
}

void BasicSquad::TryToMove() {
    moving_ = true;
    attacking_ = false;
}

void BasicSquad::Act() {
    if (attacking_) {
        Interact(_Attack);
        return;
    }

    if (moving_) {
        Interact(_Move);
        return;
    }
}

void BasicSquad::MoveTowards(const Point& other_coords) {
    if (other_coords == coords) {
        moving_ = false;
        return;
    }
    
    double distance = other_coords - coords;
    double sine = (other_coords.y - coords.y) / distance;
    double cosine = (other_coords.x - coords.x) / distance;

    double new_x = coords.x + speed_ * cosine;
    double new_y = coords.y + speed_ * sine;

    int new_x_int = static_cast<int>(new_x);
    int new_y_int = static_cast<int>(new_y);

    int old_x_int = static_cast<int>(coords.x);
    int old_y_int = static_cast<int>(coords.y);

    if (new_x_int == old_x_int && new_y_int == old_y_int) {
        return;
    }

    if (terrain_->map_[new_y][new_x] != nullptr) {
        return;
    }

    terrain_->map_[new_y][new_x] = this;
    terrain_->map_[new_y][new_x] = nullptr;
}

void BasicSquad::Interact(enum Actions action) {
    if (action == _Move) {
        MoveTowards(captured_->coords);
    }
    else if (action == _Attack) {
        if (captured_ == nullptr) {
            return;
        }

        
        //TO DO
    }
}

