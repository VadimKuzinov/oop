#include "BasicSquad.h"
#include "Terrain.h"
#include "decl.h"

#include <iostream>


int main() {
    std::vector<std::vector<BasicSquad*>> map(10, std::vector<BasicSquad*>(10));

    map[3][4] = static_cast<BasicSquad>(new GeneralSquad());

    for (int i = 0; i < 10; ++i) {
	for (int j = 0; j < 10; ++j) {
		if (map[i][j]->id == GeneralSquad) {
			std::cout << 'G';
		}
		else {
			std::cout << '_';
		}
	}
	std::cout << '\n';
    }

    return 0;
}
