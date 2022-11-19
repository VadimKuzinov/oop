#include "MapWidget.h"
#include "AbilitySpriteHelper.h"
#include "Point.h"


MapWidget::MapWidget(SDL_Renderer* renderer, SDL_Rect drawing_area) : Widget(renderer, drawing_area) {
}

void MapWidget::draw() {
    auto drawing_area = getDrawingArea();
    auto renderer = getRenderer();

    SDL_RenderCopy(renderer, backround_, NULL, &drawing_area);
    
    std::stringstream ss;
    std::string school, ability, action, fname;
    SDL_Rect src_rect, dst_rect;
    std::pair<SDL_Texture*, AbilitySpriteHelper> txt_pair;
    Point coords;
    int w, h;
    double angle;
    for (auto&& str_data : getData()) {
        ss = std::stringstream(str_data);
        ss >> school >> ability >> coords >> angle >> action;
        fname = filenames_[school][ability];
        txt_pair = spritesheets_[fname];
        SDL_QueryTexture(txt_pair.first, NULL, NULL, &w, &h);
        src_rect = txt_pair.second.getNextSpriteRectangle(action, 180 * angle / 3.14, frame_it, w, h);

        auto point = Point::withIntCfs(coords * scale_factor_);
        int x = (int)point.x;
        int y = (int)point.y;
        y = drawing_area.h - y - scale_factor_;

        SDL_Rect dst_rect = {x, y, scale_factor_, scale_factor_};
        SDL_RenderCopy(renderer, txt_pair.first, &src_rect, &dst_rect);
    }

    ++frame_it;
    freeUsedTextures();
}

std::istream& operator>>(std::istream& ifs, MapWidget& mw) {
    std::string backround_filename;
    ifs >> backround_filename;
    SDL_Surface* surface = SDL_LoadBMP(backround_filename.c_str());
    mw.backround_ = SDL_CreateTextureFromSurface(mw.getRenderer(), surface);
    SDL_FreeSurface(surface);

    std::size_t qty;
    ifs >> qty;
    std::string school, ability, fname;
    while (qty--) {
        ifs >> school >> ability >> fname;

        SDL_Surface* surface = SDL_LoadBMP(fname.c_str());
        mw.spritesheets_[fname].first = SDL_CreateTextureFromSurface(mw.getRenderer(), surface);
        SDL_FreeSurface(surface);

        mw.filenames_[school][ability] = fname;
    }

    ifs >> qty;
    while (qty--) {
        ifs >> fname;
        ifs >> mw.spritesheets_[fname].second;
    }
}

