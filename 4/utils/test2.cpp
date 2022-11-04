#include <iostream>


/*
template <>
struct Helper<std::string
*/

struct A {
    int a;

    void set(const std::string& name) {
        if (name == "name") a = 4;        
    }
};


int main() {
    return 0;
}

