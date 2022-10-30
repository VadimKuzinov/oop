#include "MenuWindow.h"
#include "Application.h"


MenuWindow::MenuWindow(int x, int y, int w, int h, SDL_Renderer* renderer, std::shared_ptr<Summoner> summoner) : 
                                                                                                        x_(x), y_(y), w_(w), h_(h), 
                                                                                                        renderer_(renderer),
                                                                                                        summoner_(summoner)
{
//    TTF_Init();
//    const char* font_path = "JustSquash.ttf";
//    font_ = TTF_OpenFont(font_path, 23);
//    if (!font_) {
//        std::cout << "FONT IN CON IS NULL\n";
//    }    
}

MenuWindow::~MenuWindow() {
    for (auto&& texture: textures_) {
        SDL_DestroyTexture(texture);
    }
//    TTF_Quit();
}

void MenuWindow::setActive(std::shared_ptr<Entity> active) {
    choices_ = {};
    active_ = active;

    if (active == nullptr) {
        addChoice(std::make_tuple<void (*)(Entity*), const char*, MenuWindow*>([](Entity* e){ return dynamic_cast<Summoner*>(e)->setSummonedId(General_); },
                    "General", nullptr));
        addChoice(std::make_tuple<void (*)(Entity*), const char*, MenuWindow*>([](Entity* e){ return dynamic_cast<Summoner*>(e)->setSummonedId(Moral_); },
                    "Moral", nullptr));
        addChoice(std::make_tuple<void (*)(Entity*), const char*, MenuWindow*>([](Entity* e){ return dynamic_cast<Summoner*>(e)->setSummonedId(GeneralHealing_); },
                    "GeneralHealing", nullptr));
        addChoice(std::make_tuple<void (*)(Entity*), const char*, MenuWindow*>([](Entity* e){ return dynamic_cast<Summoner*>(e)->setSummonedId(MoralHealing_); },
                    "MoralHealing", nullptr));
        return;
    }

    auto menu = active->getMenu();
    for (auto&& pair: menu) {
        addChoice(std::make_tuple<void (*&)(Entity*), const char*&, MenuWindow*>(pair.first, pair.second, nullptr));
    }
}

void MenuWindow::addChoice(const std::tuple<void (*)(Entity*), const char*, MenuWindow*>& choice) {
    choices_.push_back(choice);
}

void MenuWindow::draw() {
    int qty = static_cast<int>(choices_.size());
//    std::cout << "Drawing, qty  = " << qty << '\n';
    if (qty == 0) {
        ch_h_ = 0;
    }
    else {
        ch_h_ = std::min(25, h_ / qty);
    }

    //vertical line for dividing game map and menu
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer_, x_, y_, x_, y_ + h_);

    //arrange font stuff
    
    TTF_Init();
    const char* font_path = "JustSquash.ttf";//
    SDL_Color textColor = {0, 0, 0, 255};
    TTF_Font* font = TTF_OpenFont(font_path, 23);//

    //qty options
    SDL_Rect rect;
    rect.w = w_;
    rect.h = ch_h_;
    rect.x = x_;
    int text_w;
    int text_h;
     
    for (int it = 0; it < qty; ++it) {
    //    std::cout << "FONT_: " << font_ << '\n';
        SDL_Surface* surface = TTF_RenderText_Solid(font, std::get<1>(choices_[it]), textColor);
        if (surface == nullptr) {
            std::cout << "SURFACE IS NULLPTR!!!\n";
//            return;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
        text_w = surface->w;
        text_h = surface->h;
        SDL_FreeSurface(surface);
        rect.y = it * ch_h_;
        rect.w = text_w;
        rect.h = text_h;
        SDL_RenderCopy(renderer_, texture, NULL, &rect);
        SDL_RenderDrawLine(renderer_, x_, rect.y, x_ + w_, rect.y);
    }
    TTF_CloseFont(font);
    TTF_Quit();
}

void MenuWindow::catchClick(int y) { 
    int qty = static_cast<int>(choices_.size());
    y /= ch_h_;
    std::cout << "Caught: " << y << "option" << '\n';
    if (y >= qty) {
        return;
    }

    if (active_ == nullptr) {
        std::get<0>(choices_[y])(summoner_.get());
    }
    else {
        std::get<0>(choices_[y])(active_.get());
    }
}

