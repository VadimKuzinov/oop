#pragma once
#include "HealingProperty.h"
#include "GeneralSquad.h"

class GeneralHealingSquad : public GeneralSquad, public HealingProperty {
public:
    GeneralHealingSquad(enum Types type = Types::_GeneralHealingSquad);
    virtual ~GeneralHealingSquad() = default;
};
