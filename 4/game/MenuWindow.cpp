#include "MenuWindow.h"
#include "Application.h"


MenuWindow::MenuWindow(int x, int y, int w, int h, SDL_Renderer* renderer, std::shared_ptr<Entity> active) : x_(x), y_(y), w_(w), h_(h), renderer_(renderer) {
    if (active == nullptr) {
        //default menu: to do
        return;
    }

    auto menu = active->getMenu();
    for (auto&& pair: menu) {
        addChoice(std::make_tuple<void (*&)(Entity*), const char*&, MenuWindow*>(pair.first, pair.second, nullptr));
    }
}

MenuWindow::~MenuWindow() {
    for (auto&& texture: textures_) {
        SDL_DestroyTexture(texture);
    }
}

void MenuWindow::addChoice(const std::tuple<void (*)(Entity*), const char*, MenuWindow*>& choice) {
    choices_.push_back(choice);
}

void MenuWindow::draw() {
    int qty = static_cast<int>(choices_.size());
    int ch_h;
    if (qty == 0) {
        ch_h = 0;
    }
    else {
        ch_h = std::min(30, h_ / qty);
    }

    //vertical line for dividing game map and menu
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer_, x_, y_, x_, y_ + h_);

    //arrange font stuff
    TTF_Init();
    const char* font_path = "sample.ttf";
    SDL_Color textColor = {0, 0, 0, 255};
    TTF_Font* font = TTF_OpenFont(font_path, 13);

    //qty options
    SDL_Rect rect;
    rect.w = w_;
    rect.h = ch_h;
    rect.x = x_; 
    for (int it = 0; it < qty; ++it) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, std::get<1>(choices_[it]), textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
        SDL_FreeSurface(surface);
        rect.y = it * ch_h;
        SDL_RenderCopy(renderer_, texture, NULL, &rect);
        SDL_RenderDrawLine(renderer_, x_, rect.y, x_ + w_, rect.y);
    }
    TTF_Quit();
}

