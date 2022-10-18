#pragma once
#include "HealingProperty.h"
#include "ImmoralSquad.h"

class ImmoralHealingSquad : public ImmoralSquad, public HealingProperty {
public:
    ImmoralHealingSquad(Terrain*, enum Types = Types::_ImmoralHealingSquad);
    virtual ~ImmoralHealingSquad() = default;
};
