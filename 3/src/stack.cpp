#include "stack.h"

#include <iostream>


int main() {
    Stack<int, 10> st;
    st.Push(5);
    st.Push(2);
    st.Push(9);
    st.Push(4);
    st.Push(3);
    st.Push(7);
    
    std::cout << st;
    int val;
    while (!st.Empty()) {
        val = st.Pop();
        std::cout << val << std::endl;
        std::cout << st;
    }


//    std::cin >> st;
//    std::cout << st;

    Stack<int, 100> st2(std::vector<int>(15, 1337));
    std::cout << st2;

    std::vector<int> vect(10, 2222);
    Stack<int, 100> st3(vect);
    std::cout << st3;

    std::vector<int> vect2(20, 3333);
    Stack<int, 100> st4(std::move(vect2));
    std::cout << st4;

    std::vector<int> vect3 {-5, -10, -15, -20, -25};
    Stack<int, 7> st5(vect3);
    std::cout << st5;

    Stack<int, 10> st6(Stack<int, 8>(std::vector<int>(5, 55)));
    std::cout << st6;


    st6 = st5;
    std::cout << st5;
    std::cout << st6;
//    Stack<int, 10> st7 = std::vector<int>{1,2,3};:q
//    std::cout << st7;
    return 0;
}
