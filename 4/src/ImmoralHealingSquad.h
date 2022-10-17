#pragma once
#include "HealingProperty.h"
#include "ImmoralSquad.h"

class ImmoralHealingSquad : public ImmoralSquad, public HealingProperty {
public:
    ImmoralHealingSquad(enum Types type = Types::_ImmoralHealingSquad);
    virtual ~ImmoralHealingSquad() = default;
};
