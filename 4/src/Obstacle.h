#pragma once
#include "Setter.h"
#include "Entity.h"
#include "Point.h"
#include <memory>


class Terrain;

class Obstacle : public Entity {
protected:
    std::shared_ptr<Terrain> terrain_ = nullptr;
    Point coords_ = {0, 0};
    double max_hp_;
    double cur_hp_;
    int priority_;
    
    std::shared_ptr<Entity> captured_ = nullptr;
    Point target_coords_ = {0, 0};

    std::string picture_filename_;

    constexpr static auto properties_ = std::make_tuple(std::make_pair(&Obstacle::coords_, "coords"),
                                                        std::make_pair(&Obstacle::max_hp_, "max_hp"),
                                                        std::make_pair(&Obstacle::cur_hp_, "cur_hp"),
                                                        std::make_pair(&Obstacle::priority_, "priority"),
                                                        std::make_pair(&Obstacle::picture_filename_, "picture_filename"));

    void set(const std::string& name, const std::string& value) override {
        return setImpl(*this, properties_, name, value, std::make_index_sequence<std::tuple_size_v<decltype(properties_)>>{});
    }

public:
    Obstacle() = default;
    virtual ~Obstacle() = default;
    Obstacle(const Obstacle&) = default;

    std::shared_ptr<Entity> clone() const override {
        return std::shared_ptr<Entity>(new Obstacle(*this));
    }

    void setTerrain(std::shared_ptr<Terrain> terrain) override {
        terrain_ = terrain;
    }

    std::shared_ptr<Terrain> getTerrain() const {
        return terrain_;
    }

    void setCoords(Point where) override {
        coords_ = where;
    }

    void setCaptured(std::shared_ptr<Entity> captured) {
        captured_ = captured;
    }
    
    void setTargetCoords(Point target_coords);
    void receiveDamage(double) override;

    double getMaxHp() const {
        return max_hp_;
    }

    std::vector<std::pair<void (*)(std::shared_ptr<Entity>), const char*>> getMenu() const override;

    void act() override {
    }

    bool isAlive() const override;

    int getPriority() const override {
        return priority_;
    }
    Point getCoords() const override {
        return coords_;
    }

    double getCurHp() const {
        return cur_hp_;
    }

    void killMySelf() override {
        cur_hp_ = 0;
    }
    
    std::vector<std::pair<std::string, std::string>> serialize() const override;

    const std::string& getPictureFileName() const override {
        return picture_filename_;
    }
};

