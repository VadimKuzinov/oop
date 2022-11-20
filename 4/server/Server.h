#pragma once
#include "../src/Game.h"


class Server {
private:
    Game* game_;
    int sfd_;

public:
    Server(Game* game) : game_(game) {
    }

    void run();
    void run2();
};