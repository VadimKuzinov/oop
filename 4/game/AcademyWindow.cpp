#include "AcademyWindow.h"
#include "Application.h"


AcademyWindow::AcademyWindow(int x, int y, int w, int h, SDL_Renderer* renderer, std::shared_ptr<Summoner> summoner) : 
                                                                                                        x_(x), y_(y), w_(w), h_(h), 
                                                                                                        renderer_(renderer),
                                                                                                        summoner_(summoner)
{
    TTF_Init();
    const char* font_path = "JustSquash.ttf";
    font_ = TTF_OpenFont(font_path, 23);
}

AcademyWindow::~AcademyWindow() {
    clearTextures();
}

void AcademyWindow::clearTextures() {
    for (auto&& texture : textures_) {
        SDL_DestroyTexture(texture);
    }
    textures_ = {};
}

void AcademyWindow::addChoice(const std::string& choice) {
    choices_.push_back(choice);
}

void AcademyWindow::draw() {
    int qty = static_cast<int>(choices_.size());
    ch_h_ = (qty == 0 ? 0 : std::min(25, h_ / qty));

    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    
    TTF_Init();

    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Rect rect;
    rect.w = w_;
    rect.h = ch_h_;
    rect.x = x_;
    int text_w;
    int text_h;
     
    for (int it = 0; it < qty; ++it) {
        SDL_Surface* surface = TTF_RenderText_Solid(font_, choices_[it].c_str(), textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
        textures_.push_back(texture);
        text_w = surface->w;
        text_h = surface->h;
        SDL_FreeSurface(surface);
        rect.y = it * ch_h_;
        rect.w = text_w;
        rect.h = text_h;
        SDL_RenderCopy(renderer_, texture, NULL, &rect);
        SDL_RenderDrawLine(renderer_, x_, rect.y + ch_h_, x_ + w_, rect.y + ch_h_);
    }
}

void AcademyWindow::setActive(std::shared_ptr<Entity> active) {
    choices_ = {};
    auto academy = summoner_->getTerrain()->getAcademy();
    if (chosen_school_ == "") {
        for (auto&& [name, school] : academy.getSchools()) {
            choices_.push_back(name);
        }
    }
    else {
        for (auto&& [name, ability] : academy.getSchools()[chosen_school_].getAbilities()) {
            choices_.push_back(name);
        }
    }
}

void AcademyWindow::catchClick(int y) { 
    int qty = static_cast<int>(choices_.size());
    y /= ch_h_;
    if (y >= qty) {
        return;
    }

    if (chosen_school_ == "") {
        chosen_school_ = choices_[y];
        summoner_->setSummonedSchool(chosen_school_);
        setActive(nullptr);
    }
    else {
        chosen_ability_ = choices_[y];
        summoner_->setSummonedAbility(chosen_ability_);
        chosen_school_ = "";
        chosen_ability_ = "";
        setActive(nullptr);
    }
}

