#include "sprs.h"

#include <iostream>
#include <vector>
#include <tuple>


template <typename T>
class Menu {
private:
    SparseMatrix<T> sm_;
    
    template <typename U = std::size_t>
    U GetNum() {
        U result;
        bool flag = 0;
        do {
            if (std::cin.bad()) {
                throw std::ios_base::failure("IO problem");
            }
            if (flag) {
                std::cin.clear();
                std::cin.ignore();
            }
            std::cin >> result;
            flag |= 1;
            if (std::cin.eof()) {
                result = 0;
                break;
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
        std::size_t m, n;
        std::cout << "rowsCount_colsCount\n";
        m = GetNum();
        n = GetNum();
        sm_ = SparseMatrix<T>(m, n);
    }

    void D_InitWithData() {
        std::size_t m, n, c;
        std::cout << "rowsCount_colsCount_nonZeroCount\n";
        m = GetNum();
        n = GetNum();
        c = GetNum();
        std::size_t i, j;
        T value;
        std::vector<std::tuple<std::size_t, std::size_t, T>> data;
        data.reserve(c);
        std::size_t t = c;
        std::cout << "i_j_value for " << c << "times\n";
        while (t--) {
            i = GetNum();
            j = GetNum();
            value = GetNum<T>();
            data.push_back(std::make_tuple(i, j, value));
        }

        sm_ = SparseMatrix<T>(m, n, data);
    }

    void D_Add() {
        std::size_t row_i, col_i;
        T value;

        std::cout << "Enter: i_j_value\n";
        row_i = GetNum();
        col_i = GetNum();
        value = GetNum<T>();

        try {
            sm_.Add(row_i, col_i, value);
        }
        catch (std::bad_alloc& e) {
            std::cout << e.what() << '\n';
            std::cout << "Bad allocation while adding element to matrix\n";
        }
        catch (std::out_of_range& e) {
            std::cout << e.what() << '\n';
        }
    }

    void D_Get() {
        std::size_t row_i, col_i;
        std::cout << "Enter: i_j\n";
        row_i = GetNum();
        col_i = GetNum();

        T result;
        try {
            result = sm_(row_i, col_i);
        }
        catch (std::out_of_range& e) {
            std::cout << e.what() << '\n';
            return;
        }

        std::cout << "(" << row_i << ", " << col_i << ") " << result << '\n';
    }

    void D_EqualityCount() {
        std::vector<std::size_t> result;
        try {
            result = sm_.EqualityCount();
        }
        catch (std::bad_alloc& e) {
            std::cout << e.what();
            std::cout << "Bad allocation while copying data vector\n";
            return;
        }

        std::cout << "row_i\teq_count\n";
        std::size_t it = 0;
        for (auto count : result) {
            std::cout << it++ << '\t' << count << '\n';
        }
    }

    void D_Density() {
        std::cout << "Density is: " << sm_.Density() << '\n';
    }

    void D_Count() {
        std::cout << "Count of non-zero elements: " << sm_.Count() << '\n';
    }

    void D_Print() {
        std::cout << sm_;
    }

    void Start() {
        const std::vector<std::pair<void (*)(Menu*), const char*>> func_info = {
            {[](Menu* ptr){ptr->D_DoNothing();}, "EXIT"},
            {[](Menu* ptr){ptr->D_Init();}, "Init without data"},
            {[](Menu* ptr){ptr->D_InitWithData();}, "Init with data"},
            {[](Menu* ptr){ptr->D_Add();}, "Add element"},
            {[](Menu* ptr){ptr->D_Get();}, "Get element"},
            {[](Menu* ptr){ptr->D_EqualityCount();}, "Get equality count for each row"},
            {[](Menu* ptr){ptr->D_Density();}, "Get density of matrix"},
            {[](Menu* ptr){ptr->D_Count();}, "Get count of non-zero elements"},
            {[](Menu* ptr){ptr->D_Print();}, "Print matrix"},
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
            catch (std::ios_base::failure& e) {
                std::cout << e.what() << std::endl;
                break;
            }
            func_info[option].first(this);
        } while (option);
    }

public:
    Menu() {
        Start();
    }
};
