#pragma once
#include "../src/Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <vector>


class SummonerWindow {
    int x_;
    int y_;
    int w_;
    int h_;

    SDL_Renderer* renderer_;
    std::shared_ptr<Summoner> summoner_;
    std::vector<SDL_Texture*> textures_;

public:
    SummonerWindow(int x, int y, int w, int h, SDL_Renderer*, std::shared_ptr<Summoner>);
    ~SummonerWindow();

    void draw();
};

