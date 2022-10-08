#include <gtest/gtest.h>
#include <stdlib.h>

#include "stack.h"


template <class U>
void swap(U& first, U& second) {
    U u(std::move(first));
    first = std::move(second);
    second = std::move(u);
}


struct TestingParameter {
    int num;
    char* str;

    constexpr TestingParameter() : num(0), str(nullptr) {
    }

    TestingParameter(int n, const char* s) : num(n) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

    TestingParameter(TestingParameter&& other) : num(other.num), str(other.str) {
        other.str = nullptr;
    }

    TestingParameter(const TestingParameter& other) : num(other.num) {
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
    }

    TestingParameter& operator=(TestingParameter&& other) {
        if (str != nullptr) {
            delete[] str;
        }
        num = other.num;
        str = other.str;
        return *this;
    }

    TestingParameter& operator=(const TestingParameter& other) {
        TestingParameter t(other);
        swap(*this, t);
        return *this;
    }

    ~TestingParameter() noexcept {
        if (str != nullptr) {
            delete[] str;
            str = nullptr;
        }
    } 
};

using T1 = TestingParameter;

bool operator==(const T1& first, const T1& second) {
    return first.num == second.num && strcmp(first.str, second.str) == 0;
}

std::ostream& operator<<(std::ostream& os, const T1& t) {
    std::cout << '[' << t.num << ", " << t.str << ']' << std::endl;
    return os;
}


TEST(Simple, PushThenPopIsEq) {
    Stack<T1, 100> st;
    st.Push(T1(123, "ABC"));
    std::cout << st.Top();
    ASSERT_TRUE(st.Pop() == T1(123, "ABC"));    
}


TEST(Init, InitFromInstanceOfBiggerSize) {
    Stack<T1, 5> st_small;
    Stack<T1, 10> st_big;
    for (int i = 0; i < 10; ++i) {
        st_big.Push(T1(i, std::to_string(100*i).c_str()));
    }

    st_small = st_big;
    std::cout << st_small.Pop();

    for (int i = 4; i >= 0; --i) {
        EXPECT_EQ(st_small.Pop(), T1(i, std::to_string(100*i).c_str()));
    }
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
