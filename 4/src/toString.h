#pragma once
#include <string>
#include <type_traits>


template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <typename T>
concept NonArithmetic = !std::is_arithmetic_v<T>;


template <Arithmetic T>
std::string toString(T value) {
    return std::to_string(value);
}

template <NonArithmetic T>
std::string toString(T value) {
    return std::string(value);
}

