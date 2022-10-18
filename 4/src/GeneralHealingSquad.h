#pragma once
#include "HealingProperty.h"
#include "GeneralSquad.h"

class GeneralHealingSquad : public GeneralSquad, public HealingProperty {
public:
    GeneralHealingSquad(Terrain*, enum Types = Types::_GeneralHealingSquad);
    virtual ~GeneralHealingSquad() = default;
};
