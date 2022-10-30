#include "SummonerWindow.h"
#include <iostream>


SummonerWindow::SummonerWindow(int x, int y, int w, int h, SDL_Renderer* renderer, std::shared_ptr<Summoner> summoner) : 
                                                                                                        x_(x), y_(y), w_(w), h_(h), 
                                                                                                        renderer_(renderer),
                                                                                                        summoner_(summoner)
{    
    TTF_Init();
    const char* font_path = "JustSquash.ttf";
    font_ = TTF_OpenFont(font_path, 23);
}

SummonerWindow::~SummonerWindow() {
    for (auto&& texture: textures_) {
        SDL_DestroyTexture(texture);
    }
}

void SummonerWindow::draw() {
    
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer_, x_, y_, x_ + w_, y_);
    SDL_RenderDrawLine(renderer_, x_, y_, x_, y_ + h_);
    
    SDL_Color textColor = {0, 0, 0, 255};
    std::string hp_info; 

    SDL_Rect rect;
    rect.w = w_;
    rect.h = h_;
    rect.x = x_;
    int text_w;
    int text_h;

}

