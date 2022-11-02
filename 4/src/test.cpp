#include "Game.h"
#include "Utils.h"


int main() {
    Entity* e = new GeneralSquad(nullptr, {0, 0});
    std::cout << isInstanceOf<GeneralSquad>(e);
    std::cout << (typeid(GeneralSquad) == typeid(*e));
    return 0;
}
