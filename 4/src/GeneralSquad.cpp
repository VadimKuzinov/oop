#include "GeneralSquad.h"
#include "Point.h"


void GeneralSquad::update() {
    auto captured = getCaptured();
    if (captured && !captured->isAlive()) {
        captured = nullptr;
        setCaptured(captured);
    }

    if (captured) {
        setTargetCoords(captured->getCoords());
    }    
}

void GeneralSquad::move() {
    auto coords = getCoords();
    auto target_coords = getTargetCoords();
    auto terrain = getTerrain();

    double act_velocity = std::min(Point::distance(coords, target_coords), velocity_);
    auto vector_direction = Point::normalized(target_coords - coords) * act_velocity;
    auto target_point = coords + vector_direction;
    auto int_target_point = Point::withIntCfs(target_point);
    if (terrain->getMap()[int_target_point] != nullptr && terrain->getMap()[int_target_point].get() != this) {
        moving_ = false;
        return;
    }

    Point cur_int_coords_ = Point::withIntCfs(coords);
    setCoords(target_point);

    if (int_target_point == cur_int_coords_) {
        if (cur_int_coords_ == target_coords) {
            moving_ = false;
        }
        return;
    }
    terrain->getMap()[int_target_point] = terrain->getMap()[cur_int_coords_];
    terrain->getMap()[cur_int_coords_] = nullptr;
}

void GeneralSquad::giveDamage() {
    double value = damage_;
    auto captured = getCaptured();
    captured->receiveDamage(value);
}

void GeneralSquad::attack() {
    auto captured = getCaptured();
    if (captured == nullptr) {
        return;
    }

    auto distance = Point::distance(getCoords(), captured->getCoords());
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

std::vector<std::pair<void (*)(std::shared_ptr<Entity>), const char*>> GeneralSquad::getMenu() const {
    auto choices = Obstacle::getMenu();
    choices.push_back({[](std::shared_ptr<Entity> e){ return std::dynamic_pointer_cast<GeneralSquad>(e)->tryToMove(); }, "Move"});
    choices.push_back({[](std::shared_ptr<Entity> e){ return std::dynamic_pointer_cast<GeneralSquad>(e)->tryToAttack(); }, "Attack"});
    return choices;
}   

