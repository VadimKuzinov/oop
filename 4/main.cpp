#include "src/Game.h"
#include "game/Application.h"
#include <thread>


int main() {
    auto game = new Game("cfg/terrain");
    std::cout << "Game created";
    auto app = new Application(game, game->getFirstPlayer());
    std::cout << "Created";

    std::thread thr1(&Game::run, game);
//    game->run();
    std::thread thr2(&Application::loop, app);
//    app->loop();

    std::cout << "Before join";
    thr1.join();
    thr2.join();
    std::cout << "After join";

    delete app;
    delete game;

    return 0;
}

