#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../src/Game.h"
#include <vector>
#include <tuple>
#include <string>


class AcademyWindow {
private:
    int x_;
    int y_;
    int w_;
    int h_;
    int ch_h_;
   
    std::string chosen_school_;
    std::string chosen_ability_;

    SDL_Renderer* renderer_;
    TTF_Font* font_;
    std::vector<SDL_Texture*> textures_;
    
    std::shared_ptr<Summoner> summoner_;
    std::shared_ptr<Entity> active_;
    std::vector<std::string> choices_;

public:
    AcademyWindow(int x, int y, int w, int h, SDL_Renderer*, std::shared_ptr<Summoner>);
    ~AcademyWindow();

    void clearTextures();
    void setActive(std::shared_ptr<Entity> active);
    void addChoice(const std::string&);
    void draw();
    void catchClick(int y); 
};

