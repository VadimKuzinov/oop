#include <iostream>
#include <vector>


template <typename T, std::size_t SIZE>
class Stack;
 
template <typename T, std::size_t SIZE>
constexpr std::ostream& operator<<(std::ostream& os, const Stack<T, SIZE>& st) {
    std::cout << '[';
    for (auto&& el : st.arr_) {
        std::cout << el << ", ";
    }
    std::cout << ']' << "<----- TOP";
    std::cout << std::endl;
    return os;
}

template <typename T, std::size_t SIZE>
std::istream& operator>>(std::istream& is, Stack<T, SIZE>& st) {
    T val;
    std::size_t count;
    std::cin >> count;
    while (count--) {
        is >> val;
        st.Push(std::move(val));
    }
    return is;
}

template <typename T, std::size_t SIZE>
void swap(Stack<T, SIZE>& first, Stack<T, SIZE>& second) {
    auto t = std::move(first);
    first = std::move(second);
    second = std::move(t);
}

template <typename T, std::size_t SIZE = std::size_t(-1)>
class Stack {
    std::vector<T> arr_;

    friend constexpr std::ostream& operator<< <> (std::ostream&, const Stack&);
    friend std::istream& operator>> <> (std::istream&, Stack&);
    
    template <typename T_OTHER, std::size_t SIZE_OTHER>
    friend class Stack;

public:
    constexpr bool Static() const noexcept {
        return SIZE != std::size_t(-1);
    }

    constexpr Stack() {
        if (Static()) {
            arr_.reserve(SIZE);
        }
    }

    explicit constexpr Stack(const std::vector<T>& arr) : arr_(arr.size() > SIZE ? std::vector<T>(0) : arr) {
        if (arr.size() > SIZE) {
            throw std::runtime_error(
                "Size of init vector is bigger than max size"
            );                
        }

        if (Static()) {
            arr_.reserve(SIZE);
        }
    }

    template <std::size_t SIZE_OTHER>
    constexpr Stack(const Stack<T, SIZE_OTHER>& other) : Stack(other.arr_) {
    }
    
    template <std::size_t SIZE_OTHER>
    constexpr Stack<T, SIZE>& operator=(const Stack<T, SIZE_OTHER>& other) {
        Stack<T, SIZE> t(std::move(other));
        swap(*this, t);
        return *this;        
    }

    explicit constexpr Stack(std::vector<T>&& arr) : arr_(arr.size() > SIZE ? std::vector<T>(0) : std::move(arr)) {
        if (arr.size() > SIZE) {
            throw std::runtime_error(
                "Size of init vector is bigger than max size"
            );                
        }

        if (Static()) {
            arr_.reserve(SIZE);
        }
    }

    template <std::size_t SIZE_OTHER>
    constexpr Stack(Stack<T, SIZE_OTHER>&& other) : arr_(std::move(other.arr_)) {
    }

    template <std::size_t SIZE_OTHER>
    constexpr Stack<T, SIZE>& operator=(Stack<T, SIZE_OTHER>&& other) {
        if (other.arr_.size() > SIZE) {
            throw std::runtime_error(
                "Cannot assign: size of given vector is bigger than max size"
            );
        }
        arr_ = std::move(other.arr_);

        if (Static()) {
            arr_.reserve(SIZE);
        }
 
        return *this;
    }        

    constexpr void Push(const T& value) {
        if (Full()) {
            throw std::runtime_error(
                "Stack overflow"
            );                
        }
        arr_.push_back(value);
    }

    constexpr void Push(T&& value) {
         if (Full()) {
            throw std::runtime_error(
                "Stack overflow"
            );                
        }
        arr_.push_back(std::move(value));
    }

    constexpr T Pop() {
        if (Empty()) {
            throw std::runtime_error(
                "Trying to pop from empty stack"
            );                
        }
        auto result = arr_.back();
        arr_.pop_back();
        return result;
    }
   
    constexpr T& Top() {
        if (Empty()) {
            throw std::runtime_error(
                "Trying to get the top element from empty stack"
            );                
        }

        return arr_.back();
    }

    constexpr T Top() const {
        if (Empty()) {
            throw std::runtime_error(
                "Trying to get the top element from empty stack"
            );                
        }

        return arr_.back();
    }

    constexpr std::size_t Size() const noexcept {
        return arr_.size();
    }

    constexpr bool Full() const noexcept {
        return Size() == SIZE;
    }

    constexpr bool Empty() const noexcept {
        return Size() == 0;
    }

    constexpr double WorkLoad() const noexcept {
        return Static() ? (double) Size() / SIZE : 0;
    }
};

