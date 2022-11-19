#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Widget.h"


class SerializeWidget : public Widget {
private:
    TTF_Font* font_;

public:
    SerializeWidget(SDL_Renderer* renderer, const SDL_Rect&);

    void draw() override;
};
