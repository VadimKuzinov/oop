#pragma once

enum class Type {
    Obstacle_;
    General_;
    Moral_;
    GeneralHealing_;
    MoralHealing_;
    Summoner_;
};

enum class Cfg {
    Obstacle_Pr_ = 1;
    Moral_Pr_ = 2;
    General_Pr_ = 2;
    ImmoralHealing_Pr_ = 2
    GeneralHealing_Pr_ = 2
    Summoner_Pr_ = 3;

    Obstacle_Mhp_ = 1000;
    Moral_Mhp_ = 300;
    General_Mhp_ = 400;
    ImmoralHealing_Mhp_ = 200;
    GeneralHealing_Mhp_ = 250;
    Summoner_Mhp_ = 5000;   

    Moral_Stab_ = 0.00001;
    Healing_Speed_ = 3.0;
    Summoner_Energy_ = 3000;
    Summoner_Energy_Regen_Speed_ = 1.0;
    Summoner_Summon_Range_ = 5.0;
    Summoner_Energy_Accumulation_ = 3.0;
};

