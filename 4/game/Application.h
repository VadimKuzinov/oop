#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../src/Game.h"
#include "MenuWindow.h"


class Application {
private:
    Game* game_;
    Player* player_;
    int scale_factor_ = 25;
    int MAX_X_;
    int MAX_Y_;
    int MENU_W_ = 100;

    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SDL_Event event_;
    MenuWindow* menu_window_;

    void draw();

public:
    void renderCoords(int*, int*);
    void flipYInCoords(int*, int*);

    Application(Game*, Player*);
    ~Application();
    
    void loop();
};

