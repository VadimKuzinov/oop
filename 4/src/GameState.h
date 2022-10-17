#include "All.h"
#include <cstddef>


class GameState {
private:
    Terrain* terrain;

public:
    GameState(Terrain*);

    void Update();

};
