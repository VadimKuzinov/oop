#include "Obstacle.h"


Obstacle::Obstacle(Terrain* terrain, Point coords, Type id) : id_(id), terrain_(terrain), coords_(coords) {
    setDefaults();
}

void Obstacle::receiveDamage(double value) {
    std::cout << "OLD HP: " << cur_hp_ << '\n';
    cur_hp_ -= value;
    std::cout << "NEW HP: " << cur_hp_ << '\n';
}

void Obstacle::setDefaults() {
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

bool Obstacle::isAlive() const {
    return cur_hp_ > 0;
}

