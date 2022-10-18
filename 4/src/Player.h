#pragma once

#include "All.h"


class Player {
    Summoner* summoner_;
    BasicSquad* active_;

public:
    Player(Summoner*);

    void ChooseSquad(BasicSquad*);
    void MakeSquadCaptureOther(BasicSquad*);

};

