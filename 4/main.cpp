#include "src/Game.h"
#include "game/Application.h"
#include <thread>


int main() {
    auto game = new Game("cfg/terrain");
    std::cout << "Game created";
    auto app = new Application(game, game->getFirstPlayer());
//    auto app2 = new Application(game, game->getSecondPlayer());
    std::cout << "Created";

    std::thread thr1(&Game::run, game);
//    game->run();
    std::thread thr2(&Application::loop, app);
//    app->loop();
  //  std::thread thr3(&Application::loop, app2);

    std::cout << "Before join";
    thr1.join();
    thr2.join();
    //thr3.join();
    std::cout << "After join";

    delete app;
    //delete app2;
    delete game;

    return 0;
}

