#include "Terrain.h"
#include "Point.h"
#include "Summoner.h"
#include "Utils.h"
#include <memory>
#include <chrono>
#include <thread>
#include <fstream>


void Terrain::init(const std::string& file_academy, const std::string& file_terrain) {
    std::ifstream ifs(file_academy);
    ifs >> academy_;

    ifs = std::ifstream(file_terrain);
    ifs >> *this;
}

void Terrain::live() {
    using frames = std::chrono::duration<int64_t, std::ratio<1, 64>>; //64 fps
    auto nextFrame = std::chrono::system_clock::now();
    auto lastFrame = nextFrame - frames{1};
    auto summoner1 = getSummonerFirst();
    auto summoner2 = getSummonerSecond();
    
    while (summoner1->isAlive() && summoner2->isAlive()) {
        map_.clearCorpses();
        for (auto&& squad : map_) {//stlparralel
            squad->act();
        }
        std::this_thread::sleep_until(nextFrame);
        lastFrame = nextFrame;
        nextFrame += frames{1};
    }
}

void Terrain::linkSquad(std::shared_ptr<Entity> e, Point where) {
    auto casted = std::static_pointer_cast<Obstacle>(e);
    casted->coords_ = where;
    casted->terrain_ = shared_from_this();
}

void Terrain::addSummoner(std::shared_ptr<Entity> e) {
    if (summoners_.first == nullptr) {
        summoners_.first = std::dynamic_pointer_cast<Summoner>(e);
    }
    else {
        summoners_.second = std::dynamic_pointer_cast<Summoner>(e);
    }
}

void Terrain::loadSchoolsToSummoner(std::shared_ptr<Summoner> summoner) {
    for (auto&& [name, school] : academy_.getSchools()) {
        summoner->getLevelsOfSchools()[name] = 1;
    }
}

void Terrain::addSquad(std::shared_ptr<Entity> new_squad, Point where, std::shared_ptr<Summoner> summoner) {
    linkSquad(new_squad, where);
    //std::static_pointer_cast<InteractiveSquad>(new_squad)->setSummoner(summoner);
    if (typeid(*new_squad) == typeid(Summoner)) {
        addSummoner(new_squad);
    }

    map_.addSquad(new_squad, where);
}

std::istream& operator>>(std::istream& is, Terrain& terrain) {
    Point limits;
    is >> limits;
    terrain.map_.setSizes(limits);

    std::size_t qty;
    is >> qty;
    Point coords;
    std::string school, ability;
    while (qty--) {
        is >> coords >> school >> ability;
        terrain.addSquad(terrain.academy_[school][ability].getModel(), coords);
    }

    return is;
}


void Terrain::transferSquadToEmptyPlace(std::shared_ptr<Entity> squad, Point target_coords) {
    auto cur_coords = Point::withIntCfs(squad->getCoords());
    auto int_target_coords = Point::withIntCfs(target_coords);
    map_[cur_coords] = nullptr;
    map_[int_target_coords] = squad;
    std::static_pointer_cast<Obstacle>(squad)->setCoords(target_coords);
}
