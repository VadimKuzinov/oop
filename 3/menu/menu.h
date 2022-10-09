#include "../src/stack.h"
#include <vector>

template <typename T, std::size_t SIZE = std::size_t(-1)>
class Menu {
    Stack<T, SIZE> st;

    template <typename U = std::size_t>
    U GetNum() {
        U result;
        bool flag = 0;
        do {
            if (std::cin.bad()) {
                throw std::runtime_error("IO problem");
            }
            if (flag) {
                std::cin.clear();
                std::cin.ignore();
            }
            std::cin >> result;
            flag |= 1;
            if (std::cin.eof()) {
                std::cin.clear();
                std::cin.ignore();
                throw std::runtime_error("Expected number in the istream but EOF received");
            }
        } while (!std::cin.good());

        return result;
    }

    template <typename U = std::size_t>
    U GetNumWithinRange(U max_) {
        U result;
        do {
            result = GetNum();
        } while (result >= max_);
        return result;
    }

    void D_DoNothing() {
    }

    void D_Init() {
        std::cout << "Format: val#1\nval#2\n...EOF" << std::endl;
        try {
           std::cin >> st;
        }
        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    void D_Print() {
        try {
           std::cout << st;
        }
        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    void D_Push() {
        T val;
        std::cout << "Value:" << std::endl;
        std::cin >> val;
        try {
            st.Push(std::move(val));
        }
        catch (std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
    }

    void D_Pop() {
        try {
            auto val = st.Pop();
            std::cout << "Poped:\n" << val << std::endl;
        }
        catch (std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
    }

    void D_Top() {
        try {
            T& top = st.Top();
            std::cout << "TOP: " << top << std::endl;          
        }
        catch (std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
    }

    void D_Size() {
        std::cout << "Current size: " << st.Size() << std::endl;
    }

    void D_Full() {
        std::cout << "Stack is full: " << (st.Full() ? "true" : "false") << std::endl;
    }

    void D_Empty() {
        std::cout << "Stack is empty: " << (st.Empty() ? "true" : "false") << std::endl;
    }

    void D_WorkLoad() {
        std::cout << "Stack's workload is: " << st.WorkLoad() * 100 << '%' << std::endl;
    }

    void Start() {        
        const std::vector<std::pair<void (*)(Menu*), const char*>> func_info = {
            {[](Menu* ptr) {ptr->D_DoNothing(); }, "EXIT"},
            {[](Menu* ptr) {ptr->D_Init(); }, "Initialize stack from stdin"},
            {[](Menu* ptr) {ptr->D_Print(); }, "Print stack to stdout"},
            {[](Menu* ptr) {ptr->D_Push(); }, "Push"},
            {[](Menu* ptr) {ptr->D_Pop(); }, "Pop"},
            {[](Menu* ptr) {ptr->D_Top(); }, "Top"},
            {[](Menu* ptr) {ptr->D_Size(); }, "Size"},
            {[](Menu* ptr) {ptr->D_Full(); }, "Full"},
            {[](Menu* ptr) {ptr->D_Empty(); }, "Empty"},
            {[](Menu* ptr) {ptr->D_WorkLoad(); }, "Workload"},
        };

        auto Options = [&func_info]() {
            for (std::size_t it = 0; it < func_info.size(); ++it) {
                std::cout << it << ". " << func_info[it].second << '\n';
            }
        };

        std::size_t option;
        auto optionCount = func_info.size();
        do {
            Options();
            try {
                option = GetNumWithinRange(optionCount);
            }
            catch (std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                break;
            }
            func_info[option].first(this);
        } while (option);
    }

public:
    constexpr Menu() : st() {
        Start();
    }
};
