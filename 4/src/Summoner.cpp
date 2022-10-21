#include "All.h"

Summoner::Summoner(Terrain* terrain, enum Types type) : BasicSquad(terrain, type) {
}

void Summoner::SetRadius(double r) {
    radius_ = r;
}

void Summoner::Summon(enum Types type, const Point& where) {
    if (where - coords >= radius_) {
        return;
    }

    BasicSquad* new_sq;
    switch (type) {
        case _ImmoralSquad:
            new_sq = new ImmoralSquad(terrain_);
            break;
        case _GeneralSquad:
            new_sq = new GeneralSquad(terrain_);
            break;
        case _ImmoralHealingSquad:
            new_sq = new ImmoralHealingSquad(terrain_);
            break;
        case _GeneralHealingSquad:
            new_sq = new GeneralHealingSquad(terrain_);
            break;    
    }
    new_sq->summoner_ = this;
    terrain_->AddSquad(new_sq, where);
}

