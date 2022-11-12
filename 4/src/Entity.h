#pragma once
#include "Point.h"
#include <vector>
#include <memory>
#include <iostream>


class Terrain;
class Entity {
private:
    virtual void set(const std::string&, const std::string&) = 0;    
    friend std::istream& operator>>(std::istream&, std::shared_ptr<Entity>&);

public:
    virtual std::vector<std::pair<std::string, std::string>> serialize() const = 0;

public:
    virtual ~Entity() = default;
    virtual std::shared_ptr<Entity> clone() const = 0;

public:
    virtual Point getCoords() const = 0;
    virtual int getPriority() const = 0;
    virtual bool isAlive() const = 0;
    virtual void act() = 0;
    virtual void receiveDamage(double) = 0;
    virtual std::vector<std::pair<void (*)(std::shared_ptr<Entity>), const char*>> getMenu() const = 0;
    virtual const std::string& getPictureFileName() const = 0;    
};


std::istream& operator>>(std::istream&, std::shared_ptr<Entity>&);

