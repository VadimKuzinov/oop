#pragma once
#include "Game.h"


class Server {
    Game* game_;

public:
    Server(Game* game) : game_(game) {
    }

    void run();
};
