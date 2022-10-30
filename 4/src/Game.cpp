#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "Game.h"


void Game::initializeSocket() {
   //set struct info
    struct sockaddr_in server_info = {0};
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(1337);
//    server_info.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t server_info_len = sizeof(server_info);

    //create socket
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) {
    }

    //bind
    if (bind(sfd, (struct sockaddr*)&server_info, sizeof(server_info)) < 0) {
    }

    //listen
    if (listen(sfd, 0) < 0) {
    }

    //accept
    struct sockaddr client_info = {0};
    socklen_t client_info_len = sizeof(client_info);
    connfd = accept(sfd, &client_info, &client_info_len);
}

void Game::catchClicks() {
    char reply[1000];
    std::string str;
    Point coords;
    auto player1 = getFirstPlayer();
    while (1) {
        recv(connfd, reply, 1000, 0); 
        str = reply;
        std::istringstream iss(str);
        iss >> coords;
        player1->catchClick(coords);
        auto active = player1->getActive();
        if (active == nullptr) {
            std::cout << "Nulltpr for some reason" << std::endl;
        }
        if (active != nullptr) {
            std::cout << "Not nullptr!" << std::endl;
/*            auto menu_v = menu(active);
            if (active->getId() == Obstacle_)
                menu_v = menu(std::dynamic_pointer_cast<Obstacle>(active));
            else if (active->getId() ==  General_)
                menu_v = menu(std::dynamic_pointer_cast<GeneralSquad>(active));
            else if (active->getId() ==  Moral_)
                menu_v = menu(std::dynamic_pointer_cast<MoralSquad>(active));
            else if (active->getId() ==  GeneralHealing_)
                menu_v = menu(std::dynamic_pointer_cast<GeneralHealingSquad>(active));
            else if (active->getId() ==  MoralHealing_)
                menu_v = menu(std::dynamic_pointer_cast<MoralHealingSquad>(active));
            else if (active->getId() ==  Summoner_)
                menu_v = menu(std::dynamic_pointer_cast<Summoner>(active));
            
*/          auto menu_v = active->getMenu();
            std::cout << "Menu's been created!" << std::endl;
            for (auto&& [func, what] : menu_v) {
                std::cout << what << std::endl;
            }
        }

    }
}   

void Game::run() {
   // std::thread thr1(&Terrain::live, terrain_);
//  terrain_->live();    
//    std::thread thr2(&Game::catchClicks, this);

    //thr1.join();
  //  thr2.join();
  //
    std::cout << "Game is running\n";
    terrain_->live();
}   

