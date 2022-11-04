#include "Map.h"
#include "Entity.h"
#include <algorithm>


void Map::addSquad(std::shared_ptr<Entity> new_squad, Point where) {
    map_[where.y][where.x] = new_squad;
    auto it_low = std::lower_bound(begin(), end(), new_squad->getPriority(),
            [](std::shared_ptr<Entity> squad, int priority) { 
                return squad->getPriority() < priority;
            });

    squads_.insert(it_low, new_squad);
}

void Map::clearCorpses() {
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

