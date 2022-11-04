#include "Terrain.h"
#include "Point.h"
#include "Summoner.h"
#include "GeneralSquad.h"
#include "MoralSquad.h"
#include "GeneralHealingSquad.h"
#include "MoralHealingSquad.h"
#include "Utils.h"
#include <algorithm>
#include <memory>
#include <chrono>
#include <thread>


Terrain::Terrain(const std::string& file_academy, const std::string& file_terrain) {
    std::ifstream ifs(file_academy);
    ifs >> academy_;
/*
    auto schools = academy_.getSchools();
    for (auto&& [name1, school] : schools) {
        std::cout << name1 << std::endl;
        auto abilities = school.getAbilities();
        for (auto&& [name2, ability] : abilities) {
            std::cout << name2 << std::endl;
        }
    }
*/
    ifs = std::ifstream(file_terrain);
    ifs >> *this;
}

void Terrain::clearCorpses() {
    auto it = squads_.begin();
    Point coords;
    while (it != squads_.end()) {
        if (!(*it)->isAlive()) {
            coords = Point::withIntCfs((*it)->getCoords());
            map_[coords.y][coords.x] = nullptr;
            squads_.erase(it++);
        }
        else {
            ++it;
        }
    }
}

void Terrain::live() {
    using frames = std::chrono::duration<int64_t, std::ratio<1, 64>>; //64 fps
    auto nextFrame = std::chrono::system_clock::now();
    auto lastFrame = nextFrame - frames{1};
    auto summoner1 = getSummonerFirst();
    auto summoner2 = getSummonerSecond();
    while (summoner1->isAlive() && summoner2->isAlive()) {
        clearCorpses();
        for (auto&& squad : squads_) {
            squad->act();
        }
        std::this_thread::sleep_until(nextFrame);
        lastFrame = nextFrame;
        nextFrame += frames{1};
    }
}

void Terrain::addSquad(const std::string& school, const std::string& ability, Point where) { // -> addSquad(string school, string ability. get Academy[school][ability]->getInstaceWithLVl
    std::cout << "TRYING TO ADD SQUAD : " << school << " " << ability << std::endl;
    auto new_squad = academy_[school][ability].getModel();
    new_squad->setCoords(where);
    new_squad->setTerrain(this);
    map_[where.y][where.x] = new_squad;
    auto it_low = std::lower_bound(squads_.begin(), squads_.end(), new_squad->getPriority(),
            [](std::shared_ptr<Entity> squad, int priority) { 
                return squad->getPriority() < priority;
            });

    squads_.insert(it_low, new_squad);
}

std::istream& operator>>(std::istream& is, Terrain& terrain) {
    Point limits;
    is >> limits;
    terrain.MAX_X = limits.x;
    terrain.MAX_Y = limits.y;

    terrain.map_.assign(terrain.MAX_Y, std::vector<std::shared_ptr<Entity>>(terrain.MAX_X));

    std::size_t qty;
    is >> qty;
    Point coords;
    std::string school, ability;
    bool flag = false;
    while (qty--) {
        is >> coords;
        is >> school;
        is >> ability;
        std::cout << "COORDS: " << coords << std::endl;
        std::cout << "SCHOOL: " << school << std::endl;
        std::cout << "ABILITY: " << ability << std::endl;
        terrain.addSquad(school, ability, coords);
        if (school == "summoner") {
            if (!flag) {
                terrain.summoners_coords_.first = coords;
                flag = true;
            }
            else {
                terrain.summoners_coords_.second = coords;
            }
        }

    }

    return is;
}

