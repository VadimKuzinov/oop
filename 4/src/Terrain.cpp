#include "Terrain.h"
#include "Point.h"
#include "Summoner.h"
#include <algorithm>


std::istream& operator>>(std::istream& is, Terrain& terrain) {
    Point limits;
    is >> limits;
    terrain.MAX_X = limits.x;
    terrain.MAX_Y = limits.y;

    Point p1;
    Point p2;
    is >> p1 >> p2;
    
    auto summoner1 = new Summoner(&terrain);
    summoner1->coords = p1;

    auto summoner2 = new Summoner(&terrain);
    summoner2->coords = p2;
    
    terrain.summoners_ = std::make_pair<Summoner*, Summoner*>(std::move(summoner1), std::move(summoner2));

    std::size_t count_of_obstacles;
    is >> count_of_obstacles;
    std::size_t t = count_of_obstacles;
    Point obst;
    while (t--) {
        is >> obst;
        terrain.obstacles_.insert(obst);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Terrain& terrain) {
    os << "MAP_WIDTH: " << terrain.MAX_X << '\n';
    os << "MAP_HEIGHT: " << terrain.MAX_Y << '\n';
    os << "Summoner1 stands here: " << terrain.summoners_.first->coords << '\n';
    os << "Summoner2 stands here: " << terrain.summoners_.second->coords << '\n';

    os << "Number of obstacles on the map: " << terrain.obstacles_.size() << '\n';
    os << "Obstacles are in following points of the map: " << '\n';
    for (auto&& point : terrain.obstacles_) {
        os << point << ", ";
    }
    os << '\n';

    for (std::size_t y = 0; y < terrain.MAX_Y; ++y) {
        for (std::size_t x = 0; x < terrain.MAX_X; ++x) {
            if (terrain.map_[y][x] == nullptr || terrain.map_[y][x]->id == _BasicSquad) {
                continue;
            }

            std::cout << Point(x, y) << " ENUM ID: " << terrain.map_[y][x]->id << 
                " with summoner: " << (terrain.map_[y][x]->summoner_) << '\n';
        }
    }

    return os;
}

Terrain::Terrain(const std::string& filename) {
    std::ifstream ifs(filename);
    ifs >> *this;
    map_.assign(MAX_Y, std::vector<BasicSquad*>(MAX_X));
    
    for (auto&& point : obstacles_) {
        map_[point.y][point.x] = obstacle_;
    }
}

Terrain::~Terrain() {
    delete summoners_.first;
    delete summoners_.second;
    delete obstacle_;
}

BasicSquad* Terrain::obstacle_ = new BasicSquad(nullptr);

void Terrain::Live() {
    while (true) {
        for (auto&& squad : squads_) {
            squad->Act(); //squad acting depending on flags (moving_, attacking_ etc.) and using information (goal_point_)                     
        }
    }
}

void Terrain::AddSquad(BasicSquad* squad, const Point& where) {
    if (map_[where.y][where.x] != nullptr) {
        return;
    }

    auto it_low = std::lower_bound(squads_.begin(), squads_.end(), squad->priority_,
            [](BasicSquad* sq, std::size_t priority) { 
                return sq->priority_ < priority;
            });

    squads_.insert(it_low, squad);
    map_[where.y][where.x] = squad;
}

