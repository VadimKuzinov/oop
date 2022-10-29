#pragma once
#include <SDL2/SDL.h>
#include "../src/Game.h"


class Application {
private:
    Game* game_;
    Player* player_;
    int scale_factor_ = 10;
    int MAX_X_;
    int MAX_Y_;

    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SDL_Event event_;

    void draw();

public:
    void renderCoords(int*, int*);
    void flipYInCoords(int*, int*);

    Application(Game*, Player*);
    ~Application();
    
    void loop();
};

