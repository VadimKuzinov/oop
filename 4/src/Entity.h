#pragma once
#include "Point.h"
#include <vector>
#include <memory>
#include <iostream>


class Terrain;
struct Entity : public std::enable_shared_from_this<Entity> {
    virtual std::shared_ptr<Entity> clone() const = 0;
    virtual Point getCoords() const = 0;
    virtual void setCoords(Point) = 0;
    virtual void setTerrain(Terrain*) = 0;
    virtual int getPriority() const = 0;
    virtual bool isAlive() const = 0;
    virtual void act() = 0;
    virtual void receiveDamage(double) = 0;
    virtual std::vector<std::pair<void (*)(std::shared_ptr<Entity>), const char*>> getMenu() const = 0;
    virtual void killMySelf() = 0;
    virtual const std::string& getPictureFileName() const = 0;    
    virtual void set(const std::string& field_name, const std::string& value) = 0;
    virtual std::vector<std::pair<std::string, std::string>> serialize() const = 0;
    virtual ~Entity() = default;
};


std::istream& operator>>(std::istream&, std::shared_ptr<Entity>&);

