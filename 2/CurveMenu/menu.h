#pragma once

#include <iostream>
#include <vector>

#include "../Curve/Curve.h"


class Menu {
private:
    Curve cv;

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

    void D_SetL() {
        std::cout << "Enter l parameter:" << std::endl;
        auto l = GetNum<long double>();
        cv.SetL(l);
    }

    void D_SetA() {
        std::cout << "Enter a parameter:" << std::endl;
        auto a = GetNum<long double>();
        cv.SetA(a);
    }

    void D_GetL() {
        std::cout << "L is: " << cv.GetL() << std::endl;
    }

    void D_GetA() {
        std::cout << "A is: " << cv.GetA() << std::endl;
    }

    void D_GetY() {
        std::cout << "Enter x: " << std::endl;
        auto x = GetNum<long double>();
        std::cout << "Y is: " << cv.GetY(x) << std::endl;
    }

    void D_GetCurvature() {
        std::cout << "Enter x: " << std::endl;
        auto x = GetNum<long double>();
        std::cout << "Curvature is: " << cv.GetCurvature(x) << std::endl;
    }

    void D_GetR() {
        std::cout << "Enter alpha: " << std::endl;
        auto alpha = GetNum<long double>();
        std::cout << "R is: " << cv.GetRSmall(alpha) << " or " << cv.GetRBig(alpha) << std::endl;
    }

    void D_GetLoopS() {
        std::cout << "Square of loop is: " << cv.GetLoopS() << std::endl;
    }

    void D_GetInflections() {
        auto res = cv.GetInflections();
        std::cout << "Inflection points are: [";
        for (auto p : res) {
            std::cout << p << ", ";
        }
        std::cout << ']' << std::endl;
    }

    void D_Print() {
        cv.Print();
    }

    void Start() {
        const std::vector<std::pair<void (*)(Menu*), const char*>> func_info = {
            {[](Menu* ptr) {ptr->D_DoNothing(); }, "EXIT"},
            {[](Menu* ptr) {ptr->D_SetL(); }, "Set l parameter"},
            {[](Menu* ptr) {ptr->D_SetA(); }, "Set a parameter"},
            {[](Menu* ptr) {ptr->D_GetL(); }, "Get l parameter"},
            {[](Menu* ptr) {ptr->D_GetA(); }, "Get a parameter"},
            {[](Menu* ptr) {ptr->D_GetY(); }, "Get abs(y) with x coord"},
            {[](Menu* ptr) {ptr->D_GetCurvature(); }, "Get curvature at x"},
            {[](Menu* ptr) {ptr->D_GetR(); }, "Get r with angle=alpha"},
            {[](Menu* ptr) {ptr->D_GetLoopS(); }, "Get square of loop"},
            {[](Menu* ptr) {ptr->D_GetInflections(); }, "Get inflection points"},
            {[](Menu* ptr) {ptr->D_Print(); }, "Print equation"},
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