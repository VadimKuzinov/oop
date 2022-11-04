#pragma once
#include "Entity.h"
#include <typeinfo>
#include <unordered_map>
#include <iostream>
#include <memory>


class Ability;
class School;
class Academy;

std::istream& operator>>(std::istream&, Ability&);
std::istream& operator>>(std::istream&, School&);
std::istream& operator>>(std::istream&, Academy&);


class Ability {
private:
    std::string name_;
    double energy_cost_;
    int required_level_of_school_;
    std::shared_ptr<Entity> model_;
    friend std::istream& operator>>(std::istream&, Ability&);

public:
    const std::string& getName() const {
        return name_;
    }

    std::shared_ptr<Entity> getModel() const;
};

class School {
private:
    std::string name_;
    int level_ = 0;
    std::unordered_map<std::string, Ability> abilities_;
    friend std::istream& operator>>(std::istream&, School&);

public:
    const std::string& getName() const {
        return name_;
    }

    int getLevel() const {
        return level_;
    }

    Ability& operator[](const std::string&);

    const auto& getAbilities() const {
        return abilities_;
    }
};

class Academy { 
private:
    std::unordered_map<std::string, School> schools_;
    friend std::istream& operator>>(std::istream&, Academy&);

public:
    School& operator[](const std::string&);
    const auto& getSchools() const {
        return schools_;
    }
};

