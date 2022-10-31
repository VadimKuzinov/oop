#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../src/Game.h"
#include <vector>
#include <tuple>


class SummonerWindow {
private:
    int x_; 
    int y_; 
    int w_; 
    int h_; 
        
    SDL_Renderer* renderer_;
    TTF_Font* font_;

    std::shared_ptr<Summoner> summoner_;
    std::shared_ptr<Entity> active_;
    std::vector<SDL_Texture*> textures_;

public:
    SummonerWindow(int x, int y, int w, int h, SDL_Renderer*, std::shared_ptr<Summoner>);
    ~SummonerWindow();

    void clearTextures();
    void setActive(std::shared_ptr<Entity> active);
    void draw();
};

