#include "Terrain.h"
#include "Point.h"
#include "Summoner.h"
#include "GeneralSquad.h"
#include "MoralSquad.h"
#include "GeneralHealingSquad.h"
#include "MoralHealingSquad.h"
#include <algorithm>
#include <memory>
#include <chrono>
#include <thread>


Terrain::Terrain(const std::string& filename) {
    std::ifstream ifs(filename);
    ifs >> *this;
}

void Terrain::live() {
    using frames = std::chrono::duration<int64_t, std::ratio<1, 64>>; //64 fps
   //std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<int64_t, std::ratio<1, 999999960>>> 
    auto nextFrame = std::chrono::system_clock::now();
    auto lastFrame = nextFrame - frames{1};
    auto summoner1 = getSummonerFirst();
    auto summoner2 = getSummonerSecond();
    while (summoner1->isAlive() && summoner2->isAlive()) {
        for (auto&& squad : squads_) {
            squad->act(); //squad acting depending on flags (moving_, attacking_ etc.) and using information (goal_point_)                     
        }
        std::this_thread::sleep_until(nextFrame);
        lastFrame = nextFrame;
        nextFrame += frames{1};
    }
}

void Terrain::addSquad(Type id, Point where) {
    Entity* new_squad;
    switch (id) {
        case Obstacle_:
            new_squad = new Obstacle(this, where);
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

    map_[where.y][where.x] = std::shared_ptr<Entity>(new_squad);

    auto it_low = std::lower_bound(squads_.begin(), squads_.end(), new_squad->getPriority(),
            [](std::shared_ptr<Entity> squad, int priority) { 
                return squad->getPriority() < priority;
            });

    squads_.insert(it_low, map_[where.y][where.x]);
}

std::istream& operator>>(std::istream& is, Terrain& terrain) {
    Point limits;
    is >> limits;
    terrain.MAX_X = limits.x;
    terrain.MAX_Y = limits.y;

    terrain.map_.assign(terrain.MAX_Y, std::vector<std::shared_ptr<Entity>>(terrain.MAX_X));

    Point p1;
    Point p2;
    is >> p1 >> p2;

    terrain.summoners_coords_ = {p1, p2};

    terrain.addSquad(Summoner_, p1);
    terrain.addSquad(Summoner_, p2);

    std::size_t count_of_obstacles;
    is >> count_of_obstacles;
    std::size_t t = count_of_obstacles;
    Point obst_coords;
    while (t--) {
        is >> obst_coords;
        terrain.addSquad(Obstacle_, obst_coords);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Terrain& terrain) {
    os << "MAP_WIDTH: " << terrain.MAX_X << '\n';
    os << "MAP_HEIGHT: " << terrain.MAX_Y << '\n';

    for (int y = 0; y < terrain.MAX_Y; ++y) {
        for (int x = 0; x < terrain.MAX_X; ++x) {
            if (terrain.map_[y][x] == nullptr) {
                continue;
            }

            std::string object_name;
            switch (terrain.map_[y][x]->getId()) {
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
            
            std::cout << Point{static_cast<double>(x),static_cast<double>(y)} << ": " << object_name << '\n';
        }
    }

    return os;
}

