#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../src/Game.h"
#include "MenuWindow.h"
#include "SummonerWindow.h"
#include "AcademyWindow.h"
#include <memory>
#include <unordered_map>


class Application {
private:
    Game* game_;
    Player* player_;
    int scale_factor_ = 25;
    int MAX_X_;
    int MAX_Y_;
    int MENU_W_ = 250; //200

    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SDL_Event event_;
    SDL_Texture* backround_;
    std::unordered_map<std::string, SDL_Texture*> textures_;

    MenuWindow* menu_window_;
    SummonerWindow* summoner_window_;
    AcademyWindow* academy_window_;

    void draw();
    void drawCircle(int, int, int);
    void drawSquad(std::shared_ptr<Entity>);

public:
    void renderCoords(int*, int*);
    void flipYInCoords(int*, int*);

    Application(Game*, Player*);
    ~Application();
    
    void loop();
};

