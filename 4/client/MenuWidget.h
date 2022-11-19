#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Widget.h"


class MenuWidget : public Widget {
private:
    TTF_Font* font_;

public:
    MenuWidget(SDL_Renderer*, const SDL_Rect&);

    void draw() override;
};
