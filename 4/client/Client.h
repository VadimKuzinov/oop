#pragma once
#include "../game/Application.h"
#include "Drawer.h"


class Client {
private:
    Drawer* drawer_;
    int sfd_;

public:
    void setDrawer(Drawer* drawer) {
        drawer_ = drawer;
    }

    void connectToServer();
    void act();
    void receiveData(char* data);
};

