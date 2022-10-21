#include "Terrain.h"
#include "Point.h"
#include "Summoner.h"
#include <algorithm>
#include <memory>


std::istream& operator>>(std::istream& is, Terrain& terrain) {
    Point limits;
    is >> limits;
    terrain.MAX_X = limits.x;
    terrain.MAX_Y = limits.y;

    terrain.map_.assign(MAX_Y, std::vector<std::shared_ptr<Base>>(MAX_X));

    Point p1;
    Point p2;
    is >> p1 >> p2;
   
    addSquad(Summoner_, p1);
    addSquad(Summoner_, p2);

    std::size_t count_of_obstacles;
    is >> count_of_obstacles;
    std::size_t t = count_of_obstacles;
    Point obst_coords;
    while (t--) {
        is >> obst_coords;
        addSquad(Obstacle_, obst_coords);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Terrain& terrain) {
    os << "MAP_WIDTH: " << terrain.MAX_X << '\n';
    os << "MAP_HEIGHT: " << terrain.MAX_Y << '\n';

    for (std::size_t y = 0; y < terrain.MAX_Y; ++y) {
        for (std::size_t x = 0; x < terrain.MAX_X; ++x) {
            if (terrain.map_[y][x] == nullptr) {
                continue;
            }

            std::string object_name;
            switch (terrain.map_[y][x]->id_) {
                case Obstacle_:
                    object_name = "Obstacle";
                    break;
                case General_:
                    object_name = "General";
                    break;
                case Moral_:
                    object_name = "Moral";
                    break;
                case GeneralHealing_:
                    object_name = "GeneralHealing";
                    break;
                case MoralHealing_:
                    object_name = "MoralHealing";
                    break;
                case Summoner_:
                    object_name = "Summoner";
                    break;
            }
            
            std::cout << Point{x, y} << ": " << object_name << '\n';
        }
    }

    return os;
}

Terrain::Terrain(const std::string& filename) {
    std::ifstream ifs(filename);
    ifs >> *this;
    map_.assign(MAX_Y, std::vector<std::shared_ptr<Base>>(MAX_X));
}

void Terrain::live() {
    while (true) {
        for (auto&& squad : squads_) {
            squad->act(); //squad acting depending on flags (moving_, attacking_ etc.) and using information (goal_point_)                     
        }
    }
}

void Terrain::addSquad(Type id, Point where) {
    Base* new_squad;
    switch (id) {
        case Obstacle_:
            new_squad = new Base(this, where);
            break;
        case General_:
            new_squad = new GeneralSquad(this, where);
            break;
        case Moral_:
            new_squad = new MoralSquad(this, where);
            break;
        case GeneralHealing_:
            new_squad = new GeneralHealingSquad(this, where);
            break;
        case MoralHealing_:
            new_squad = new MoralHealingSquad(this, where);
            break;
        case Summoner_:
            new_squad = new Summoner(this, where);
            break;
    }

    map_[where.y][where.x] = std::shared_ptr<Base>(new_squad);

    auto it_low = std::lower_bound(squads_.begin(), squads_.end(), new_squad_->priority_,
            [](std::shared_ptr<Base> squad, int priority) { 
                return squad->priority_ < priority;
            });

    squads_.insert(it_low, new_squad_);
}
