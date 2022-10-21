#include "src/All.h"

#include <iostream>
#include <vector>


void Print(const std::vector<std::vector<BasicSquad*>>& map) {
    for (int i = 0; i < (int)map.size(); ++i) {
        for (int j = 0; j < (int)map[0].size(); ++j) {
            std::cout << (map[i][j] && map[i][j]->id == _GeneralSquad ? 'G' : '_');
        }
        std::cout << '\n';
    }
}


using bs = BasicSquad;
void swap(bs*& bs1, bs*& bs2) {
    bs* t = bs1;
    bs1 = bs2;
    bs2 = t;
}


int main() {
    std::vector<std::vector<BasicSquad*>> map(30, std::vector<BasicSquad*>(50));

    map[3][4] = dynamic_cast<BasicSquad*>(new GeneralSquad);


    BasicSquad bs;
    std::cout << (int)bs.id << std::endl;


    ImmoralSquad is;
    std::cout << (int)is.id << std::endl;

    GeneralSquad gs;
    std::cout << (int)gs.id << std::endl;

    BasicSquad* gs_p = new GeneralSquad;
    std::cout << (int)gs_p->id << std::endl;

    char c;
    int i = 3;
    int j = 4;
    while (true) {
        std::cin >> c;
        switch (c) {
            case 'w':
                swap(map[i][j], map[i-1][j]);
                --i; 
                break;
            case 's':
                swap(map[i][j], map[i+1][j]);
                ++i;
                break;
            case 'a':
                swap(map[i][j], map[i][j-1]);
                --j;
                break;
            case 'd':
                swap(map[i][j], map[i][j+1]);
                ++j;
                break;
        }
        Print(map);
    }

    return 0;
}
