#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "Game.h"

/*
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
    }
}   
*/
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

