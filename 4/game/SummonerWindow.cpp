#include "SummonerWindow.h"
#include <iostream>


SummonerWindow::SummonerWindow(int x, int y, int w, int h, SDL_Renderer* renderer, std::shared_ptr<Summoner> summoner) : 
                                                                                                        x_(x), y_(y), w_(w), h_(h), 
                                                                                                        renderer_(renderer),
                                                                                                        summoner_(summoner),
                                                                                                        active_(summoner_)
{    
    TTF_Init();
    const char* font_path = "GummyBears.ttf";
    font_ = TTF_OpenFont(font_path, 18);
}

void SummonerWindow::clearTextures() {
    for (auto&& texture : textures_) {
        SDL_DestroyTexture(texture);
    }
    textures_ = {};
}

void SummonerWindow::clear() {
    TTF_CloseFont(font_);
}

void SummonerWindow::draw() { 
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    
    std::string hp_info; 

    SDL_Rect rect;
    rect.x = x_;
    rect.w = w_;
    rect.h = h_;
    auto serialized = active_->serialize();

    TTF_Init();
    SDL_Color color = {0, 0, 0, 255};
    std::string field;
    int y_pos = y_ + h_;
    for (auto&& [value, name] : serialized) {
        field = name + ": " + value;
        TTF_SizeText(font_, field.c_str(), &rect.w, &rect.h);
        y_pos -= rect.h;
        rect.y = y_pos;
        SDL_Surface* surface = TTF_RenderText_Solid(font_, field.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
        textures_.push_back(texture);
        SDL_FreeSurface(surface);
        SDL_RenderCopy(renderer_, texture, NULL, &rect);
    }

    SDL_RenderDrawLine(renderer_, x_, y_pos, x_ + w_, y_pos);
}

void SummonerWindow::setActive(std::shared_ptr<Entity> active) {
    if (active) {
        active_ = active;
    }
    else {
        active_ = summoner_;
    }
}

