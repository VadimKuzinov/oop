#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "AbilitySpriteHelper.h"
#include "Widget.h"


class Drawer {
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    int height_;
    int width_;
    int right_stripe_width_ = 250;

    Widget* map_widget_;
    Widget* menu_widget_;
    Widget* serialize_widget_;

public:
    Drawer(int width, int height, const std::string& cfg_filename);

    void Drawer::receiveData(const std::vector<std::string>& map, 
                             const std::vector<std::string>& menu, 
                             const std::vector<std::string>& serialize);
    
    void catchClick(int x, int y);
    void draw();
};

