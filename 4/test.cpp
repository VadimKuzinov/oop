#include "src/Game.h"
#include "server/Server.h"
#include <thread>


int main() {
    auto game = new Game("cfg/academy", "cfg/map3");
    auto server = new Server(game);

    //auto thr1 = std::thread(&Game::run, game);
    //auto thr2 = std::thread(&Server::run2, server);

    //thr1.join();
    //thr2.join();

    server->run2();


    delete server;
    delete game;
    return 0;
}