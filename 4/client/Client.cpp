#include "Client.h"
#include <sstream>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>



void Client::connectToServer() {
    struct sockaddr_in client_info = {0};
    client_info.sin_family = AF_INET;
    client_info.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    client_info.sin_port = htons(1337);
    socklen_t client_info_len = sizeof(client_info);
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(sfd, (struct sockaddr*)&client_info, client_info_len);
    puts("connected");
}


void Client::act() {
    int x, y;
    bool running = true;
    std::string data_to_send;
    SDL_Event event_;
    char buf[1024];
    while (running) {
        recv(sfd_, buf, 1024, 0);
        receiveData(buf);
        drawer_->draw();
        while (SDL_PollEvent(&event_)) {
            switch (event_.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x, &y);
                    drawer_->catchClick(x, y);
                    break;
               case SDL_KEYDOWN:
                    if (event_.key.keysym.sym == SDLK_a) {
                    }
                    break;
            }
        }
        SDL_Delay(21);
    }
}


void Client::receiveData(char* data) {
    auto received = std::string(data);
    auto ss = std::stringstream(received);

    std::vector<std::vector<std::string>> widgets;
    std::size_t qty;
    std::string s;
    for (auto it = 0; it < 3; ++it) {
        ss >> qty;
        while (qty--) {
            ss >> s;
            widgets[it].push_back(s);
        }
    }

    drawer_->receiveData(widgets[0], widgets[1], widgets[2]);
}
