#include "Server.h"
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>


template <typename T>
void pushVarAsChars(std::vector<char>& v, const T& var) {
    std::string s = toString(var);
    for (char c : s) {
        v.push_back(c);
    }
}

void interactWithClient(int sfd, std::shared_ptr<Player> player) {
    char reply_from_client[100];
    std::stringstream ss;
    std::string type;
    Point where;
    std::vector<char> result = {};
    auto terrain = player->getSummoner()->getTerrain();
    auto qty = terrain->getMap().getQuantityOfSquads()+1;
    pushVarAsChars(result, qty);
    result.push_back('\n');

    bool is_enemy;
    for (auto&& squad : terrain->getMap()) {
        pushVarAsChars(result, squad->getSchoolName());
        result.push_back(' ');
        pushVarAsChars(result, squad->getAbilityName());
        result.push_back(' ');
        pushVarAsChars(result, squad->getCoords());
        result.push_back(' ');
        pushVarAsChars(result, typeid(*squad) == typeid(Obstacle) ? 1 : std::static_pointer_cast<InteractiveSquad>(squad)->getActingAngle());
        result.push_back(' ');
        pushVarAsChars(result, applyFunctionToCasted(typeid(*squad), ActingStatus{}, squad));
        result.push_back(' ');
        pushVarAsChars(result, std::static_pointer_cast<Obstacle>(squad)->getCurHp() / std::static_pointer_cast<Obstacle>(squad)->getMaxHp());
        result.push_back(' ');
        pushVarAsChars(result, typeid(*squad) == typeid(Obstacle) ? 1 : (int)(squad != player->getSummoner() && 
                                    std::static_pointer_cast<InteractiveSquad>(squad)->getSummoner() != player->getSummoner()));
        result.push_back('\n');
    }

    pushVarAsChars(result, "active ");
    auto active = player->getActive();
    if (active && !active->isAlive()) {
        player->resetActive();
        active = nullptr;
    }

    if (active == nullptr) {
        pushVarAsChars(result, Point{-1, -1});
    }
    else {
        pushVarAsChars(result, active->getCoords());
    }

    result.push_back('\n');
    std::shared_ptr<Entity> e = (active == nullptr ? player->getSummoner() : active);
    auto serialized = e->serialize();

    auto choices = player->getMenuOptions();
    pushVarAsChars(result, choices.size());
    result.push_back('\n');
    for (auto&& option_name : choices) {
        pushVarAsChars(result, option_name);
        result.push_back('\n');
    }

    pushVarAsChars(result, serialized.size());
    result.push_back('\n');

    for (auto&& pair : serialized) {
        pushVarAsChars(result, pair.second);
        result.push_back(':');
        result.push_back(' ');
        pushVarAsChars(result, pair.first);
        result.push_back('\n');
    }
    result.push_back('\0');
    char *msg = result.data();
    //std::cout << "STRLEN IS: " << strlen(msg) << std::endl;
    int t = send(sfd, msg, 10000, 0);

    t = recv(sfd, reply_from_client, 100, 0);
    //std::cout << "GOT " << t << " bytes from player\n";
    if (reply_from_client[0] != '\0') {
        ss = std::stringstream(reply_from_client);
        ss >> type >> where;
        //std::cout << "1TYPE: " << type << ", POINT: " << where << std::endl;
        player->catchClick(type, where);
    }
}

void Server::run() {
    puts("Server is running");
    struct sockaddr_in server_info = {0};
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(1337);
    socklen_t server_info_len = sizeof(server_info);
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sfd, (struct sockaddr*)&server_info, sizeof(server_info));
    listen(sfd, 0);
    struct sockaddr client_info = {0};
    socklen_t client_info_len = sizeof(client_info);
    int connfd = accept(sfd, &client_info, &client_info_len);

    auto player1 = game_->getFirstPlayer();
    auto player2 = game_->getSecondPlayer();

    using frames = std::chrono::duration<int64_t, std::ratio<1, 5>>; //64 fps
    auto nextFrame = std::chrono::system_clock::now();
    auto lastFrame = nextFrame - frames{1};
    char* msg;
    auto terrain = game_->getTerrain();
    std::vector<char> result;
    int it = 0;

    char reply_from_client[100];
    while (true) {
        result = {};
        auto qty = terrain->getMap().getQuantityOfSquads();
        pushVarAsChars(result, qty);
        result.push_back('\n');

        for (auto&& squad : terrain->getMap()) {
            pushVarAsChars(result, squad->getSchoolName());
            result.push_back(' ');
            pushVarAsChars(result, squad->getAbilityName());
            result.push_back(' ');
            pushVarAsChars(result, squad->getCoords());
            result.push_back(' ');
            pushVarAsChars(result, std::static_pointer_cast<InteractiveSquad>(squad)->getActingAngle());
            result.push_back(' ');
            pushVarAsChars(result, applyFunctionToCasted(typeid(*squad), ActingStatus{}, squad));
            result.push_back('\n');
        }

        auto active = player1->getActive();
        if (!active->isAlive()) {

        }

        std::shared_ptr<Entity> e = (active == nullptr ? player1->getSummoner() : active);
        auto serialized = e->serialize();

        result.push_back('0');
        result.push_back('\n');

        pushVarAsChars(result, serialized.size());
        result.push_back('\n');

        for (auto&& pair : serialized) {
            pushVarAsChars(result, pair.first);
            result.push_back(' ');
            pushVarAsChars(result, pair.second);
            result.push_back('\n');
        }
        msg = result.data();
        //std::cout << msg << std::endl;
        int t = send(connfd, msg, strlen(msg) + 1, 0);
        std::cout << t << " BYTES ARE SENDED " << "on " << it++ << " iteration\n";  
        std::this_thread::sleep_until(nextFrame);
        lastFrame = nextFrame;
        nextFrame += frames{1};

        t = recv(connfd, reply_from_client, 100, 0);
        std::cout << "RECEIVED: " << t << " bytes\n";
        std::cout << "message from client: " << reply_from_client << std::endl;
    }
}

void Server::run2() {
    int opt = 1;  
    int new_socket, activity, max_sd;
    struct sockaddr_in address;  

    std::pair<int, int> client_sfd_pair = {0, 0};

    int server_socket = socket(AF_INET , SOCK_STREAM , 0);
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));

    struct sockaddr_in socket_info;  
    socket_info.sin_family = AF_INET;  
    socket_info.sin_addr.s_addr = INADDR_ANY;  
    socket_info.sin_port = htons( 1337 );  

    bind(server_socket, (struct sockaddr *)&socket_info, sizeof(socket_info));
    printf("Listener on port %d \n", 1337);  

    listen(server_socket, 3);
    
    socklen_t socket_info_len = sizeof(socket_info);
    puts("Waiting for connections ...");  

    fd_set readfds;

    using frames = std::chrono::duration<int64_t, std::ratio<1, 64>>; //64 fps
    auto nextFrame = std::chrono::system_clock::now();
    auto lastFrame = nextFrame - frames{1};
    while(true)  
    {
        FD_ZERO(&readfds);  
        FD_SET(server_socket, &readfds);  
        max_sd = server_socket;  

        if (client_sfd_pair.first > 0) {
            FD_SET(client_sfd_pair.first, &readfds);
            if (client_sfd_pair.first > max_sd) {
                max_sd = client_sfd_pair.first;
            }
        }
        if (client_sfd_pair.second > 0) {
            FD_SET(client_sfd_pair.second, &readfds);
            if (client_sfd_pair.second > max_sd) {
                max_sd = client_sfd_pair.second;
            }
        }
        
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        activity = select( max_sd + 1 , &readfds , NULL , NULL , &tv);  
    
        int a, b, c;
        a = FD_ISSET(server_socket, &readfds);
        b = FD_ISSET(client_sfd_pair.first, &readfds);
        c = FD_ISSET(client_sfd_pair.second, &readfds);
        if (a|b|c)
            //std::cout << a << b << c << std::endl;

        if (FD_ISSET(server_socket, &readfds))  
        {
            std::cout << "inside server isset" << std::endl;
            new_socket = accept(server_socket, (struct sockaddr *)&socket_info, &socket_info_len);
            printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
  
            (client_sfd_pair.first == 0 ? client_sfd_pair.first : client_sfd_pair.second) = new_socket;
        }  

        if (FD_ISSET(client_sfd_pair.first, &readfds)) {
            interactWithClient(client_sfd_pair.first, game_->getFirstPlayer());
        }

        if (FD_ISSET(client_sfd_pair.second, &readfds)) {
            interactWithClient(client_sfd_pair.second, game_->getSecondPlayer());
        }

        game_->getTerrain()->goToTheNextIteration();
        std::this_thread::sleep_until(nextFrame);
        lastFrame = nextFrame;
        nextFrame += frames{1};
    }  
}
