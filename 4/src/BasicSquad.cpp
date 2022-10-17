#include "BasicSquad.h"
#include <cmath>


BasicSquad::BasicSquad(enum Types type): id(type) {
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

    coords.x += speed_ * cosine;
    coords.y += speed_ * sine;
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

