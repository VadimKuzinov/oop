#pragma once
#include <vector>
#include <typeinfo>
#include <memory>
#include <array>

#include "Entity.h"
#include "Obstacle.h"
#include "GeneralSquad.h"
#include "MoralSquad.h"
#include "GeneralHealingSquad.h"
#include "MoralHealingSquad.h"
#include "Summoner.h"

struct BasePtrToDerivedInstance {
    template <typename T>
    std::shared_ptr<Entity> operator()(std::shared_ptr<T> ptr) {
        return std::shared_ptr<Entity>(new T);
    }
};

template <typename Func, typename Head>
auto applyFunctionToCastedImpl(const std::type_info& type, Func func, std::shared_ptr<Entity> e) {
    return func(std::dynamic_pointer_cast<Head>(e));
}

template <typename Func, typename Head, typename... Args>
auto applyFunctionToCastedImpl(const std::type_info& type, Func func, std::shared_ptr<Entity> e) -> std::enable_if<sizeof...(Args) != 0, decltype(func(e))>::type{ 
    if (typeid(Head) == type) {
        return func(std::dynamic_pointer_cast<Head>(e));
    }

    return applyFunctionToCastedImpl<Func, Args...>(type, func, e);
}

template <typename Func>
auto applyFunctionToCasted(const std::type_info& type, Func func, std::shared_ptr<Entity> e = nullptr) {
    return applyFunctionToCastedImpl<Func, Obstacle, GeneralSquad, MoralSquad, GeneralHealingSquad, MoralHealingSquad, Summoner>(type, func, e);
}
/*
template <typename T>
concept Moving = requires(T sq) {
    sq.tryToMove();
};

template <typename T>
concept Attacking = requires(T sq) {
    sq.tryToAttack();
};

template <typename T>
concept Summoning = requires(T sq) {
    sq.tryToSummon();
};

template <typename T>
concept Accumulating = requires(T sq) {
    sq.tryToAccumulate();
};

template <typename T>
concept Upgrading = requires(T sq) {
    sq.tryToUpgrade();
};

template <typename T>
concept Healing = requires(T sq) {
    sq.tryToHeal();
};
*/

inline const std::type_info& getTypeInfoFromString(const std::string& type) {
    if (type == "Obstacle") {
        return typeid(Obstacle);
    }
    else if (type == "GeneralSquad") {
        return typeid(GeneralSquad);
    }
    else if (type == "MoralSquad") {
        return typeid(MoralSquad);
    }
    else if (type == "GeneralHealingSquad") {
        return typeid(GeneralHealingSquad);
    }
    else if (type == "MoralHealingSquad") {
        return typeid(MoralHealingSquad);
    }
    else if (type == "Summoner") {
        return typeid(Summoner);
    }
    else {
        return typeid(Entity);
    }
}
