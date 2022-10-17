#include "Terrain.h"
#include "Point.h"
#include "Summoner.h"


std::istream& operator>>(std::istream& is, Terrain& terrain) {
    Point limits;
    is >> limits;
    terrain.MAX_X = limits.x;
    terrain.MAX_Y = limits.y;

    Point p1;
    Point p2;
    is >> p1 >> p2;
    
    auto summoner1 = new Summoner;
    summoner1->coords = p1;

    auto summoner2 = new Summoner;
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

    return os;
}

Terrain::Terrain(const std::string& filename) {
    std::ifstream ifs(filename);
    ifs >> *this;
    map_.assign(MAX_Y, std::vector<BasicSquad*>(MAX_X));
    
    for (auto&& point : obstacles_) {
        map_[point.y][point.x] = obstacle_; //TO FIX
    }
}

Terrain::~Terrain() {
    delete summoners_.first;
    delete summoners_.second;
    delete obstacle_;
}

BasicSquad* Terrain::obstacle_ = new BasicSquad;

