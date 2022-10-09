#include <gtest/gtest.h>

#include <string_view>
#include "../src/stack.h"


struct TestStruct {
    int i;
    std::string_view s;

    std::pair<double, bool> p;

    constexpr TestStruct() : i(0), s(""), p(std::make_pair<double, bool>(0.0, false)) {
    }

    constexpr TestStruct(int i_, std::string_view s_, std::pair<double, bool> p_) : i(i_), s(s_), p(p_) {
    }
};

bool operator==(const TestStruct& t1, const TestStruct& t2) {
    return t1.i == t2.i && t1.s == t2.s && t1.p.first == t2.p.first && t1.p.second == t2.p.second;
}


TEST(Exception, InitFromTooLargeVector) {
    std::vector<int> vec(101, 1337);
    try {
        Stack<int, 100> st(vec);
        FAIL();
    }
    catch (std::runtime_error& e) {
    }
}


TEST(Exception, InitFromTooLargeStack) {
    Stack<int, 100> st1(std::vector<int>(100, 1337));
    try {
        Stack<int, 80> st2(st1);
        FAIL();
    }
    catch (std::runtime_error& e) {
    }
}


TEST(Exception, PushToFullStack) {
    Stack<int, 100> st(std::vector<int>(100, 1337));
    try {
        st.Push(1337);
        FAIL();
    }
    catch (std::runtime_error& e) {
    }
}


TEST(Exception, PopFromEmptyStack) {
    Stack<int, 5> st;
    try {
        st.Pop();
        FAIL();
    }
    catch (std::runtime_error& e) {
    }
}


TEST(ConstructorCivility, Copy) {
    Stack<int, 100> st1;
    for (int i = 0; i < 33; ++i) {
        st1.Push(i * 3);
    }

    Stack<int, 200> st2(st1);

    int i1, i2;
    try {
        while (!st1.Empty()) {
            i1 = st1.Pop();
            i2 = st2.Pop();
            ASSERT_EQ(i1, i2);
        }
    }
    catch (std::runtime_error& e) {
        FAIL();
    }
}


TEST(ConstructorCivility, Move) {
    Stack<int, 200> st1;
    for (int i = 0; i < 150; ++i) {
        st1.Push(i * 5);
    }

    Stack<int, 170> st2(std::move(st1));

    int i1, i2;
    try {
        while (!st1.Empty()) {
            i1 = st1.Pop();
            i2 = st2.Pop();
            ASSERT_EQ(i1, i2);
        }
    }
    catch (std::runtime_error& e) {
        FAIL();
    }
}


TEST(AssignmentCivility, Copy) {
    Stack<int, 300> st1;
    for (int i = 0; i < 234; ++i) {
        st1.Push(i * 7);
    }

    Stack<int, 500> st2;
    for (int i = 0; i < 456; ++i) {
        st2.Push(i * 8);
    }

    st2 = st1;
    st1.Top() = 1337;
    ASSERT_NE(st1.Top(), st2.Top());
    st1.Top() = st2.Top();
    int i1, i2;
    try {
        while (!st1.Empty()) {
            i1 = st1.Pop();
            i2 = st2.Pop();
            ASSERT_EQ(i1, i2);
        }
    }
    catch (std::runtime_error& e) {
        FAIL();
    }
}


TEST(AssignmentCivility, Move) {
    Stack<int, 1300> st1;
    for (int i = 0; i < 1234; ++i) {
        st1.Push(i * 9);
    }

    Stack<int, 1500> st2;
    for (int i = 0; i < 1456; ++i) {
        st2.Push(i * 10);
    }

    st2 = std::move(st1);
    ASSERT_EQ(st1.Size(), 0);
    int i2;
    try {
        for (int i = 1233; !st2.Empty(); --i) {
            i2 = st2.Pop();
            ASSERT_EQ(i * 9, i2);
        }
    }
    catch (std::runtime_error& e) {
        FAIL();
    }
}


using T = TestStruct;
TEST(PushPop, RValueStruct) {
    Stack<T, 100> st;
    st.Push(T(1337, "StringTest", std::make_pair<double, bool>(-1337.1337, true)));
    ASSERT_EQ(T(1337, "StringTest", std::make_pair<double, bool>(-1337.1337, true)), st.Pop());
}


TEST(PushPop, LValueStruct) {
    Stack<T, 100> st;
    auto t = T(1337, "StringTest", std::make_pair<double, bool>(-1337.1337, true));
    st.Push(t);
    ASSERT_EQ(T(1337, "StringTest", std::make_pair<double, bool>(-1337.1337, true)), st.Pop());
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

