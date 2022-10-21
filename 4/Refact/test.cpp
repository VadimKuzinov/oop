#include <iostream>
#include <memory>


struct Container {
    int a = 5;

    Container(int b) : a(b) {
    }

    ~Container() {
        std::cout << "Deleted" << std::endl;
    }
};


int main() {
    using namespace  std;
    auto c1 = make_shared<Container>(3);
    auto c2(c1);
    auto c3(c1);
    c3 = nullptr;
    c2 = nullptr;
    c1 = nullptr;    
    while (1) {}
    return 0;
}
