#include "Application.h"
#include "../src/Point.h"
#include "../src/Utils.h"
#include <iostream>


Application::Application(Game* game, Player* player) : game_(game), player_(player) {
    auto terrain = game->getTerrain();
    MAX_X_ = scale_factor_ * terrain->getMap().getWidth();
    MAX_Y_ = scale_factor_ * terrain->getMap().getHeight();

    SDL_Init(SDL_INIT_EVERYTHING);
    window_ = SDL_CreateWindow("sss", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAX_X_ + MENU_W_, MAX_Y_, SDL_WINDOW_SHOWN);
    renderer_ = SDL_CreateRenderer(window_, -1, 0);

    menu_window_ = new MenuWindow(MAX_X_, 0, MENU_W_, 4 * MAX_Y_ / 5, renderer_, player_->getSummoner());
    summoner_window_ = new SummonerWindow(MAX_X_, 4 * MAX_Y_ / 5, MENU_W_, MAX_Y_ / 5, renderer_, player_->getSummoner());
    academy_window_ = new AcademyWindow(MAX_X_, 4 * MAX_Y_ / 5, MENU_W_, MAX_Y_ / 5, renderer_, player_->getSummoner());

    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderClear(renderer_);

    auto academy = terrain->getAcademy();
    auto schools = academy.getSchools();
    for (auto&& [name, school] : schools) {
        auto abilities = school.getAbilities();
        for (auto&& [name, ability] : abilities) {
            auto model = ability.getModel();
            auto pct_file = model->getPictureFileName();
            SDL_Surface* surface = SDL_LoadBMP(pct_file.c_str());
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
            textures_[pct_file] = texture;
            SDL_FreeSurface(surface);
        }
    }

    SDL_Surface* backround = SDL_LoadBMP("grey.bmp");
    backround_ = SDL_CreateTextureFromSurface(renderer_, backround);
    SDL_FreeSurface(backround);
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
    SDL_Rect rect;
    rect.x = 0; rect.y = 0; rect.w = MAX_X_; rect.h = MAX_Y_;
    SDL_RenderCopy(renderer_, backround_, NULL, &rect);

    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer_, MAX_X_, 0, MAX_X_, MAX_Y_);

    summoner_window_->clearTextures();
    summoner_window_->setActive(player_->getActive());
    summoner_window_->draw();

    menu_window_->clearTextures();
    menu_window_->setActive(player_->getActive());

    academy_window_->clearTextures();
    academy_window_->setActive(player_->getActive());

    if (player_->getActive() == nullptr) {
        academy_window_->draw();
    }
    else {
        menu_window_->draw();
    }

    for (auto&& squad : game_->getTerrain()->getMap()) {
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
       // std::cout << "Loop iter\n";
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
                        if (player_->getActive() == nullptr) {
                            academy_window_->catchClick(y);
                        }
                        else {
                            menu_window_->catchClick(y);
                        }
                        break;
                    }
                    renderCoords(&x, &y);
                    flipYInCoords(&x, &y);
                    //std::cout << "After correcting: " << x << ' ' << y << '\n';
                    player_->catchClick(Point{static_cast<double>(x), static_cast<double>(y)});
                    break;
               case SDL_KEYDOWN:
                    if (event_.key.keysym.sym == SDLK_a) {
                        player_->resetActive();
                    }
                    break;
            }
        }
        draw();
        SDL_Delay(21);
    }
}

void Application::drawSquad(std::shared_ptr<Entity> e) {
    auto pct_file = e->getPictureFileName();

    auto coords = e->getCoords();
    coords = Point::withIntCfs(coords);
    int x0 = static_cast<int>(coords.x);
    int y0 = static_cast<int>(coords.y);

    int x = scale_factor_ * x0;
    int y = MAX_Y_ - scale_factor_ * (y0 + 1);

    auto point = Point::withIntCfs(e->getCoords() * scale_factor_);
    x = (int)point.x;
    y = (int)point.y;
    y = MAX_Y_ - y - scale_factor_;

    SDL_Rect rect;
    rect.x = x; rect.y = y; rect.w = scale_factor_; rect.h = scale_factor_;
    SDL_RenderCopy(renderer_, textures_[pct_file], NULL, &rect);

    if (player_->getActive() == e) {
        SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);      
        drawCircle(x, y, scale_factor_ * 1.4);
    }

    SDL_Rect hp_bar;
    hp_bar.x = x;
    hp_bar.y = y - scale_factor_ / 4;
    auto casted_to_obstacle = std::dynamic_pointer_cast<Obstacle>(e);
    hp_bar.w = scale_factor_ * (casted_to_obstacle->getCurHp() / casted_to_obstacle->getMaxHp());
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
    while (x >= y) {
        SDL_RenderDrawPoint(renderer_, x0 + x, y0 + y);
        SDL_RenderDrawPoint(renderer_, x0 + y, y0 + x);
        SDL_RenderDrawPoint(renderer_, x0 - y, y0 + x);
        SDL_RenderDrawPoint(renderer_, x0 - x, y0 + y);
        SDL_RenderDrawPoint(renderer_, x0 - x, y0 - y);
        SDL_RenderDrawPoint(renderer_, x0 - y, y0 - x);
        SDL_RenderDrawPoint(renderer_, x0 + y, y0 - x);
        SDL_RenderDrawPoint(renderer_, x0 + x, y0 - y);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

