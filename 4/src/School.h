#pragma once
//#include "Entity.h"
//#include "Obstacle.h"
#include "GeneralSquad.h"
//#include "MoralSquad.h"
//#include "GeneralHealingSquad.h"
//#include "MoralHealingSquad.h"
//#include "Summoner.h"
#include <typeinfo>
#include <unordered_map>


struct School {
    virtual const std::type_info& getTypeInfo() const = 0;
    virtual void setInitialParameters() = 0;
};


struct SchoolGeneralSquad : School {
    const std::type_info& getTypeInfo() const override {
        return typeid(GeneralSquad);
    }

    void setInitialParameters() override {
    }
};


struct SchoolSummoner : School {
    const std::type_info& getTypeInfo() const override {
        return typeid(Summoner);
    }

    void setInitialParameters() override {
    }
};


struct SchoolObstacle : School {
    const std::type_info& getTypeInfo() const override {
        return typeid(Obstacle);
    }

    void setInitialParameters() override {
    }
};



class Ability {

};


class School {
private:
    int level_;
    std::unordered_map<std::string, Ability> abilities_;

public:
    int getLevel() const {
        return level_;
    }

    Ability& operator[](const std::string&);
};


class Academy { 
private:
    std::unordered_map<std:string, School> schools_;

public:
    School& operator[](const std::string&);
};

