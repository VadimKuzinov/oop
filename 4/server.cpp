#include "server/Server.h"


int main() {
    auto game = new Game("cfg/academy", "cfg/map3");
    auto server = new Server(game);

    server->run();


    delete server;
    delete game;
    return 0;
}
