#pragma once

enum Type {
    Obstacle_,
    General_,
    Moral_,
    GeneralHealing_,
    MoralHealing_,
    Summoner_,
};


extern int Obstacle_Pr_;
extern int Moral_Pr_;
extern int General_Pr_;
extern int ImmoralHealing_Pr_;
extern int GeneralHealing_Pr_;
extern int Summoner_Pr_;

extern int Obstacle_Mhp_;
extern int Moral_Mhp_;
extern int General_Mhp_;
extern int ImmoralHealing_Mhp_;
extern int GeneralHealing_Mhp_ ;
extern int Summoner_Mhp_;   

extern double Moral_Stab_;
extern double Healing_Speed_;
extern double Summoner_Energy_;
extern double Summoner_Energy_Regen_Speed_;
extern double Summoner_Summon_Range_;
extern double Summoner_Energy_Accumulation_;

