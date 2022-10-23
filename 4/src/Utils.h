#pragma once
#include "Squads.h"


template <Type


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

template <typename T>
concept Capturing = requires(T sq, std::shared_ptr<Base> captured) {
    sq.setCaptured(captured);
};

