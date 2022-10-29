#include "Application.h"
#include "../src/Point.h"
#include "../src/Utils.h"
#include <iostream>


Application::Application(Game* game, Player* player) : game_(game), player_(player) {
    auto terrain = game->getTerrain();
    MAX_X_ = scale_factor_ * terrain->MAX_X;
    MAX_Y_ = scale_factor_ * terrain->MAX_Y;

    SDL_Init(SDL_INIT_EVERYTHING);
    window_ = SDL_CreateWindow("sss", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAX_X_, MAX_Y_, SDL_WINDOW_SHOWN);
    renderer_ = SDL_CreateRenderer(window_, -1, 0);

    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderClear(renderer_); 
}

Application::~Application() {
    std::cout << "trying to destroy window...\n";
    SDL_DestroyWindow(window_);
    std::cout << "destroyed!\n";
    SDL_Quit();
    std::cout << "quitted\n";
}

void Application::renderCoords(int* x, int* y) {
    std::cout << "OLD X: " << *x << '\n';
    *x /= scale_factor_;
    std::cout << "NEW X: " << *y << '\n';
    *y /= scale_factor_;
}

void Application::flipYInCoords(int* x, int* y) {
    *y = MAX_Y_ / scale_factor_ - *y;
}

void Application::draw() {
    int x, y;
    int r, g, b;
    for (std::size_t y0 = 0; y0 < MAX_Y_ / scale_factor_; ++y0) {
        for (std::size_t x0 = 0; x0 < MAX_X_ / scale_factor_; ++x0) {
            x = scale_factor_ * x0;
            y = scale_factor_ * y0;
            y = MAX_Y_ - y;
            SDL_Rect rect;
            rect.x = x;
            rect.y = y;
            rect.w = scale_factor_;
            rect.h = scale_factor_;
   
            auto terrain = game_->getTerrain(); 
            if (terrain->map_[y0][x0] == nullptr) {
                continue;
            }

            switch (terrain->map_[y0][x0]->getId()) {
                case Obstacle_:
                    r = 0;
                    g = 0;
                    b = 0;
                    break;
                case General_:
                    r = 100;
                    g = 100;
                    b = 100;
                    break;
                case Moral_:
                    r = 200;
                    g = 200;
                    b = 200;
                    break;
                case GeneralHealing_:
                    r = 100;
                    g = 0;
                    b = 0;
                    break;
                case MoralHealing_:
                    r = 0;
                    g = 100;
                    b = 0;
                    break;
                case Summoner_:
                    r = 0;
                    g = 0;
                    b = 100;
                    break;
            }

            SDL_SetRenderDrawColor(renderer_, r, g, b, 255);
            SDL_RenderFillRect(renderer_, &rect);
        }
    }

    SDL_RenderPresent(renderer_);
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderClear(renderer_); 
}

void Application::loop() {
    int x, y;
    bool running = true;
    std::shared_ptr<Summoner> s = nullptr;
    SDL_Window* popup = nullptr;
    std::vector<std::pair<void (*)(std::shared_ptr<Entity>), const char*>> menu;
    std::shared_ptr<Entity> active;
    while (running) {
        std::cout << "Loop iter\n";
        while (SDL_PollEvent(&event_)) {
            switch (event_.type) {
                case SDL_QUIT:
                    std::cout << "SDLQUIT SITUATION\n";
                    running = false;
                    s = player_->getSummoner();
                    std::cout << "Summoner coords: " << s->getCoords() << '\n';
                    std::cout << "Summoner hp: " << s->getCurHp() << '\n';
                    s->receiveDamage(100000);
                    std::cout << "Summoner hp: " << s->getCurHp() << '\n';
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x, &y);
                    std::cout << "Mouse state: " << x << ' ' << y << '\n';
                    renderCoords(&x, &y);
                    std::cout << "After rendering: " << x << ' ' << y << '\n';
                    flipYInCoords(&x, &y);
                    std::cout << "After flipping: " << x << ' ' << y << '\n';
                    player_->catchClick(Point{x, y});
                    break;
                case SDL_KEYDOWN:
                    if (event_.key.keysym.sym == SDLK_m) {
                         active = player_->getActive();
                         if (active == nullptr) {
                             break;
                         }

                         menu = active->getMenu();
                         for (auto&& [func, what] : menu) {
                             std::cout << what << '\n';
                         }
                    }
//                    switch (event_.key.keysym.sym) {
//                  }
                    
            }
            draw();
        }
        SDL_Delay(1000);
    }
}


