#pragma once
#include "ImmoralSquad.h"

class GeneralSquad : public ImmoralSquad {
protected:
    double morality;

public:
    GeneralSquad(enum Types type = Types::_GeneralSquad);
    virtual ~GeneralSquad() = default;
};
