#include "Terrain.h"
#include "Point.h"
#include "Summoner.h"
#include "GeneralSquad.h"
#include "MoralSquad.h"
#include "GeneralHealingSquad.h"
#include "MoralHealingSquad.h"
#include "Utils.h"
#include <memory>
#include <chrono>
#include <thread>


Terrain::Terrain(const std::string& file_academy, const std::string& file_terrain) {
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
        for (auto&& squad : map_) {
            squad->act();
        }
        std::this_thread::sleep_until(nextFrame);
        lastFrame = nextFrame;
        nextFrame += frames{1};
    }
}

void Terrain::addSummoner(std::shared_ptr<Entity> e) {
    if (summoners_.first == nullptr) {
        summoners_.first = std::dynamic_pointer_cast<Summoner>(e);
    }
    else {
        summoners_.second = std::dynamic_pointer_cast<Summoner>(e);
    }
}

void Terrain::addSquad(const std::string& school, const std::string& ability, Point where) { // -> addSquad(string school, string ability. get Academy[school][ability]->getInstaceWithLVl
    auto new_squad = academy_[school][ability].getModel();
    new_squad->setCoords(where);
    new_squad->setTerrain(this);
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
        terrain.addSquad(school, ability, coords);
    }

    return is;
}

