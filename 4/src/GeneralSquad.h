#pragma once
#include "ImmoralSquad.h"

class GeneralSquad : public ImmoralSquad {
protected:
    double morality;

public:
    GeneralSquad(Terrain*, enum Types = Types::_GeneralSquad);
    virtual ~GeneralSquad() = default;
};
