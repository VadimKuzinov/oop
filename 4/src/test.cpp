#include "Game.h"
#include "Utils.h"


int main() {
    auto e = createPtrToInstanceOf(typeid(GeneralSquad));
    std::cout << e->getCoords();
    return 0;
}
