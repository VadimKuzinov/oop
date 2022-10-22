#pragma once

enum Type {
    Obstacle_,
    General_,
    Moral_,
    GeneralHealing_,
    MoralHealing_,
    Summoner_,
};


int Obstacle_Pr_ = 1;
int Moral_Pr_ = 2;
int General_Pr_ = 2;
int ImmoralHealing_Pr_ = 2;
int GeneralHealing_Pr_ = 2;
int Summoner_Pr_ = 3;

int Obstacle_Mhp_ = 1000;
int Moral_Mhp_ = 300;
int General_Mhp_ = 400;
int ImmoralHealing_Mhp_ = 200;
int GeneralHealing_Mhp_ = 250;
int Summoner_Mhp_ = 5000;   

double Moral_Stab_ = 0.00001;
double Healing_Speed_ = 3.0;
double Summoner_Energy_ = 3000;
double Summoner_Energy_Regen_Speed_ = 1.0;
double Summoner_Summon_Range_ = 5.0;
double Summoner_Energy_Accumulation_ = 3.0;

