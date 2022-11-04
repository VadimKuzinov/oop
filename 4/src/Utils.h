#pragma once
#include <vector>
#include <typeinfo>
#include <memory>

#include "Entity.h"
/*
#include "Obstacle.h"
#include "GeneralSquad.h"
#include "MoralSquad.h"
#include "GeneralHealingSquad.h"
#include "MoralHealingSquad.h"
#include "Summoner.h"
*/

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
/*
class Entity;
class Obstacle;
class GeneralSquad;
class MoralSquad;
class GeneralHealingSquad;
class MoralHealingSquad;
class Summoner;
*/
template <typename Head>
inline std::shared_ptr<Entity> createPtrToInstanceOfImpl(const std::type_info& type) {
    if (typeid(Head) == type) {
        return std::shared_ptr<Entity>(new Head);
    }

    return nullptr;
}

template <typename Head, typename... Args>
inline std::enable_if<sizeof...(Args) != 0, std::shared_ptr<Entity>>::type createPtrToInstanceOfImpl(const std::type_info& type) {
    if (typeid(Head) == type) {
        return std::shared_ptr<Entity>(new Head);
    }
    
    return createPtrToInstanceOfImpl<Args...>(type);
}

inline std::shared_ptr<Entity> createPtrToInstanceOf(const std::type_info& type) {
    return createPtrToInstanceOfImpl<Obstacle, GeneralSquad, MoralSquad, GeneralHealingSquad, MoralHealingSquad, Summoner>(type);
}

template <typename U, typename T>
inline constexpr bool isInstanceOf(const T* v) {
    return typeid(U) == typeid(*v);
}

