#pragma once
#include <vector>
#include <list>
#include <memory>


class Map {
private:
    std::vector<std::vector<std::shared_ptr<Entity>>> map_;
    std::pair<std::shared_ptr<Summoner>, std::shared_ptr<Summoner>> summoners_;
    std::list<std::shared_ptr<Entity>> squads_;

public:
    std::size_t getWidth() const {
        return map_[0].size();
    }

    std::size_t getHeight() const {
        return map_.size();
    }
};
