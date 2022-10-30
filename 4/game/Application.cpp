#include "Application.h"
#include "../src/Point.h"
#include "../src/Utils.h"
#include <iostream>


Application::Application(Game* game, Player* player) : game_(game), player_(player) {
    auto terrain = game->getTerrain();
    MAX_X_ = scale_factor_ * terrain->MAX_X;
    MAX_Y_ = scale_factor_ * terrain->MAX_Y;

    //menu at the right side of screen
    SDL_Init(SDL_INIT_EVERYTHING);
    window_ = SDL_CreateWindow("sss", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAX_X_ + MENU_W_, MAX_Y_, SDL_WINDOW_SHOWN);
    renderer_ = SDL_CreateRenderer(window_, -1, 0);

    menu_window_ = new MenuWindow(MAX_X_, 0, MENU_W_, 4 * MAX_Y_ / 5, renderer_, player_->getSummoner());
    summoner_window_ = new SummonerWindow(MAX_X_, 4 * MAX_Y_ / 5, MENU_W_, MAX_Y_ / 5, renderer_, player_->getSummoner());

    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderClear(renderer_); 
}

Application::~Application() {
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Application::renderCoords(int* x, int* y) {
    *x /= scale_factor_;
    *y /= scale_factor_;
}

void Application::flipYInCoords(int* x, int* y) {
    *y = MAX_Y_ / scale_factor_ - *y - 1;
}

void Application::draw() {
    summoner_window_->draw();
    menu_window_->setActive(player_->getActive());
    menu_window_->draw();

    //summoner_window_->draw();

    for (auto&& squad : game_->getTerrain()->squads_) {
        drawSquad(squad);
    }

    SDL_RenderPresent(renderer_);
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderClear(renderer_);
    TTF_Quit(); 
}

void Application::loop() {
    int x, y;
    bool running = true;
    std::shared_ptr<Summoner> s = nullptr;
    SDL_Window* popup = nullptr;
    std::vector<std::pair<void (*)(Entity*), const char*>> menu;
    std::shared_ptr<Entity> active;
    while (running) {
        std::cout << "Loop iter\n";
        while (SDL_PollEvent(&event_)) {
            switch (event_.type) {
                case SDL_QUIT:
                    running = false;
                    s = player_->getSummoner();
                    s->killMySelf();
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x, &y);
                    if (x >= MAX_X_) {
                        menu_window_->catchClick(y);
                        break;
                    }
                    renderCoords(&x, &y);
                    flipYInCoords(&x, &y);
                    std::cout << "After correcting: " << x << ' ' << y << '\n';
                    player_->catchClick(Point{x, y});
                    break;
            }
        }
        draw();
        SDL_Delay(21);
    }
}

void Application::drawSquad(std::shared_ptr<Entity> e) {
    int r, g, b;
    switch (e->getId()) {
        case Obstacle_:
            r = 0; g = 0; b = 0;
            break;
        case General_:
            r = 100; g = 100; b = 100;
            break;
        case Moral_:
            r = 200; g = 200; b = 200;
            break;
        case GeneralHealing_:
            r = 100; g = 0; b = 0;
            break;
        case MoralHealing_:
            r = 0; g = 100; b = 0;
            break;
        case Summoner_:
            r = 0; g = 0; b = 100;
            break;
    }

    auto coords = e->getCoords();
    coords = Point::withIntCfs(coords);
    int x0 = static_cast<int>(coords.x);
    int y0 = static_cast<int>(coords.y);

    int x = scale_factor_ * x0;
    int y = MAX_Y_ - scale_factor_ * (y0 + 1);

    SDL_Rect rect;
    rect.x = x; rect.y = y; rect.w = scale_factor_; rect.h = scale_factor_;
    SDL_SetRenderDrawColor(renderer_, r, g, b, 255);
    SDL_RenderFillRect(renderer_, &rect);

    if (player_->getActive() == e) {
        std::cout << "PLAYER: " << player_ << '\n';
        drawCircle(x, y, scale_factor_ * 1.4);
    }

    if (e->getId() == Obstacle_) {
        return;
    }

    SDL_Rect hp_bar;
    hp_bar.x = x;
    hp_bar.y = y - scale_factor_ / 4;
    hp_bar.w = scale_factor_;
    hp_bar.h = scale_factor_ / 4;
    SDL_SetRenderDrawColor(renderer_, 11, 102, 35, 111);
    SDL_RenderFillRect(renderer_, &hp_bar);
}

void Application::drawCircle(int x0, int y0, int radius) {
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);
    while (x >= y)
    {
        SDL_RenderDrawPoint(renderer_, x0 + x, y0 + y);
        SDL_RenderDrawPoint(renderer_, x0 + y, y0 + x);
        SDL_RenderDrawPoint(renderer_, x0 - y, y0 + x);
        SDL_RenderDrawPoint(renderer_, x0 - x, y0 + y);
        SDL_RenderDrawPoint(renderer_, x0 - x, y0 - y);
        SDL_RenderDrawPoint(renderer_, x0 - y, y0 - x);
        SDL_RenderDrawPoint(renderer_, x0 + y, y0 - x);
        SDL_RenderDrawPoint(renderer_, x0 + x, y0 - y);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

