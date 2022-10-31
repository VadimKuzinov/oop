#pragma once
#include "Type.h"
#include "Point.h"
#include <vector>


class Entity {
public:
    virtual Type getId() const = 0;
    virtual Point getCoords() const = 0;
    virtual int getPriority() const = 0;
    virtual bool isAlive() const = 0;
    virtual void act() = 0;
    virtual void receiveDamage(double) = 0;
    virtual std::vector<std::pair<void (*)(Entity*), const char*>> getMenu() const = 0;
    virtual void killMySelf() = 0;
    virtual std::vector<std::pair<std::string, std::string>> serialize() const = 0;
    virtual ~Entity() = default;
};

