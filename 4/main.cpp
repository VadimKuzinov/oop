#include "src/Game.h"
#include "game/Application.h"
#include <thread>


int main() {
    auto game = new Game("cfg/academy", "cfg/map");
    auto app = new Application(game, game->getFirstPlayer());
//    auto app2 = new Application(game, game->getSecondPlayer());
    std::thread thr1(&Game::run, game);
 //   game->run();
    std::thread thr2(&Application::loop, app);
//    app->loop();
  //  std::thread thr3(&Application::loop, app2);

    thr1.join();
    thr2.join();
    //thr3.join();

    delete app;
    //delete app2;
    delete game;

    return 0;
}

