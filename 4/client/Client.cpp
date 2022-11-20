#include "Client.h"
#include <sstream>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include <chrono>


void Client::connectToServer() {
    struct sockaddr_in client_info = {0};
    client_info.sin_family = AF_INET;
    client_info.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    client_info.sin_port = htons(1337);
    socklen_t client_info_len = sizeof(client_info);
    sfd_ = socket(AF_INET, SOCK_STREAM, 0);
    int t = connect(sfd_, (struct sockaddr*)&client_info, client_info_len);
    if (t == 0)
        puts("connected");
}

void Client::act() {
    int x, y;
    bool running = true;
    std::string data_to_send;
    SDL_Event event_;
    char buf[100000];
    int t;
    const char* temp = "";
    send(sfd_, temp, 100, 0);
    using frames = std::chrono::duration<int64_t, std::ratio<1, 64>>;
    auto next_frame = std::chrono::system_clock::now() + frames{1};
    auto cur_frame = std::chrono::system_clock::now();
    std::string no_action = "none 0 0";
    std::string to_send;
    while (running) {
        to_send = "";
        t = recv(sfd_, buf, 100000, 0);
        if (t != 10000) continue;
        receiveData(buf);
        std::cout << "RECEIVED: " << t << " bytes\n";
        cur_frame = std::chrono::system_clock::now();
        if (cur_frame >= next_frame) {
            drawer_->draw();
            next_frame += frames{1};
        }

        std::pair<std::string, Point> caught;
        while (SDL_PollEvent(&event_)) {
            switch (event_.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x, &y);
                    caught = drawer_->catchClick(x, y);
                    to_send = caught.first + " " + std::string(caught.second);
                    break;
               case SDL_KEYDOWN:
                    if (event_.key.keysym.sym == SDLK_a) {
                    }
                    break;
                default:
                    break;
            }
        }
        if (to_send != "")
            send(sfd_, to_send.c_str(), 100, 0);
        else 
            send(sfd_, no_action.c_str(), 100, 0);
    }
}

void Client::receiveData(char* data) {
    std::cout << "received:\n";
    std::cout << data << std::endl;
    auto received = std::string(data);
    auto ss = std::stringstream(received);
    std::vector<std::vector<std::string>> widgets(3);
    std::size_t qty;
    std::string s;
    for (auto it = 0; it < 3; ++it) {
        ss >> qty;
        if (qty > 1000) std::cout << "Qty is too big" << std::endl;
        ss.ignore(1);
        while (qty--) {
            std::getline(ss, s);
            widgets[it].push_back(s);
        }
    }

    drawer_->receiveData(widgets[0], widgets[1], widgets[2]);
}
