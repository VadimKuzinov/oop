#pragma once
#include "Setter.h"
#include "Entity.h"
#include "Point.h"
#include <memory>


class Obstacle : public Entity {
private:
    std::shared_ptr<Terrain> terrain_;
    Point coords_ = {0, 0};
    friend class Terrain;

protected:
    double max_hp_;
    double cur_hp_;
    int priority_;

    std::string picture_filename_;

private:
    constexpr static auto properties_ = std::make_tuple(std::make_pair(&Obstacle::max_hp_, "max_hp"),
                                                        std::make_pair(&Obstacle::cur_hp_, "cur_hp"),
                                                        std::make_pair(&Obstacle::priority_, "priority"),
                                                        std::make_pair(&Obstacle::picture_filename_, "picture_filename"),
                                                        std::make_pair(&Obstacle::coords_, "coords"));

    void set(const std::string& name, const std::string& value) override {
        return setImpl(*this, properties_, name, value);
    }

protected:
    constexpr static auto getProperties() {
        return properties_;
    }

public:
    std::vector<std::pair<std::string, std::string>> serialize() const override {
        return serializeImpl(*this, properties_);
    }

public:
    virtual ~Obstacle() = default;

    std::shared_ptr<Entity> clone() const override {
        return std::shared_ptr<Entity>(new Obstacle(*this));
    }

protected:
    void setCoords(Point new_coords) {
        coords_ = new_coords;
    }

public:
    std::shared_ptr<Terrain> getTerrain() const {
        return terrain_;
    }

    Point getCoords() const override {
        return coords_;
    }

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

    double getCurHp() const {
        return cur_hp_;
    }

    const std::string& getPictureFileName() const override {
        return picture_filename_;
    }
};

