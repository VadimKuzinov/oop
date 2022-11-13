#pragma once
#include <vector>
#include <typeinfo>
#include <memory>
#include <string>

#include "Concepts.h"
#include "Entity.h"
#include "Obstacle.h"
#include "InteractiveSquad.h"
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


struct MenuCaller {
    template <typename T>
    auto operator()(std::shared_ptr<T> e) {
        std::vector<std::pair<void (*)(std::shared_ptr<Entity>), std::string>> result;

        if constexpr (Attacking<T>) {
            result.push_back({[](std::shared_ptr<Entity> e) { std::dynamic_pointer_cast<T>(e)->tryToAttack(); }, "Attack"});
        }

        if constexpr (Moving<T>) {
            result.push_back({[](std::shared_ptr<Entity> e) { std::dynamic_pointer_cast<T>(e)->tryToMove(); }, "Move"});
        }

        if constexpr (Healing<T>) {
            result.push_back({[](std::shared_ptr<Entity> e) { std::dynamic_pointer_cast<T>(e)->tryToHeal(); }, "Heal"});
        }

        if constexpr (Summoning<T>) {
            result.push_back({[](std::shared_ptr<Entity> e) { std::dynamic_pointer_cast<T>(e)->tryToSummon(); }, "Summon"});
        }

        if constexpr (Accumulating<T>) {
            result.push_back({[](std::shared_ptr<Entity> e) { std::dynamic_pointer_cast<T>(e)->tryToAccumulate(); }, "Accumulate"});
        }

        if constexpr (Upgrading<T>) {
            result.push_back({[](std::shared_ptr<Entity> e) { std::dynamic_pointer_cast<T>(e)->tryToUpgrade(); }, "Upgrade"});
        }

        return result;
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
    return applyFunctionToCastedImpl<Func, Obstacle, InteractiveSquad, GeneralSquad, MoralSquad, GeneralHealingSquad, MoralHealingSquad, Summoner>(type, func, e);
}

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

