#include "client/Client.h"


int main() {
    auto drawer = new Drawer(1746, 918, "cfg/all");
    auto client = new Client;
    client->setDrawer(drawer);
    client->connectToServer();
    client->act();
    return 0;
}
