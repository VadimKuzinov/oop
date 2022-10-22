#include "Base.h"


Base::Base(Terrain* terrain, Point coords, Type id) : id_(id), terrain_(terrain), coords_(coords) {
    setDefaults();
}

void Base::receiveDamage(double value) {
    cur_hp_ -= value;
}

void Base::setDefaults() {
    switch (id_) {
        case Obstacle_:
            priority_ = Obstacle_Pr_;
            max_hp_ = Obstacle_Mhp_;
            cur_hp_ = max_hp_;
            break;
        case General_:
            priority_ = General_Pr_;
            max_hp_ = General_Mhp_;
            cur_hp_ = max_hp_;
            break;
        case Moral_:
            priority_ = Moral_Pr_;
            max_hp_ = Moral_Mhp_;
            cur_hp_ = max_hp_;
            break;
        case GeneralHealing_:
            priority_ = GeneralHealing_Pr_;
            max_hp_ = GeneralHealing_Mhp_;
            cur_hp_ = max_hp_;
           break;
        case MoralHealing_:
            priority_ = ImmoralHealing_Pr_;
            max_hp_ = ImmoralHealing_Mhp_;
            cur_hp_ = max_hp_;
          break;
        case Summoner_:
            priority_ = Summoner_Pr_;
            max_hp_ = Summoner_Mhp_;
            cur_hp_ = max_hp_;
         break;        
    }
}

bool Base::isAlive() const {
    return cur_hp_ > 0;
}

