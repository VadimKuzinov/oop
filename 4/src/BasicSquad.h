#pragma once

#include <cstddef>
#include "Enums.h"
#include "Point.h"


class BasicSquad {
public:
    enum Types id;
    
    Point coords;
    BasicSquad* captured_ = nullptr;
    std::size_t priority_;
    std::size_t population_;
    double speed_;
    double max_hp_;
    double current_overall_hp_;
    double attack_range_;

    bool attacking_ = false;
    bool moving_ = false;

public:
    BasicSquad(enum Types = _BasicSquad);
    virtual ~BasicSquad() = default;

    void SetCoords(const Point& p);
    void SetPriority(std::size_t priority);
    void SetPopulation(std::size_t population);
    void SetSpeed(double speed);
    void SetMaxHp(double max_hp);
    void SetAttackRange(double attack_range);

    void TryToAttack();
    void TryToMove();

    void Act(); //virtual
    void Interact(enum Actions); //with captured    
    void MoveTowards(const Point& p); //move by command from outside                                
};

