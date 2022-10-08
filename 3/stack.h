template <typename T, std::size_t SIZE>
class Stack; 

template <typename T, std::size_t SIZE>
class Stack {
    std::size_t size_ = 0;
    T arr_[SIZE];

    template <typename U, std::size_t SIZE_OTHER>
    friend class Stack;

    std::size_t max(std::size_t first, std::size_t second) const noexcept {
        return first < second ? second : first;
    }

    template <class U>
    void swap(U& first, U& second) const {
        U t(std::move(first));
        first = std::move(second);
        second = std::move(t);
    }

public:
    constexpr Stack() {
    }

    Stack(std::size_t count, T* arr) : size_(max(count, SIZE)) {
        for (std::size_t it = 0; it < size_; ++it) {
            arr_[it] = arr[it];
        }
    }

    template <std::size_t SIZE_OTHER>
    Stack(const Stack<T, SIZE_OTHER>& other) : size_(max(other.size_, SIZE)) {
        for (std::size_t it = 0; it < size_; ++it) {
            arr_[it] = other.arr_[it];
        }
    }

    template <std::size_t SIZE_OTHER>
    Stack(Stack<T, SIZE_OTHER>&& other) : size_(max(other.size_, SIZE)), arr_(other.arr_) {
        other.size_ = 0;
    }

    template <std::size_t SIZE_OTHER>
    Stack<T, SIZE>& operator=(const Stack<T, SIZE_OTHER>& other) {
        Stack<T, SIZE> temporary(other);
        swap(*this, temporary);
        return *this;
    }

    template <std::size_t SIZE_OTHER>
    Stack<T, SIZE>& operator=(Stack<T, SIZE_OTHER>&& other) {
        Stack<T, SIZE> temporary(other);
        swap(*this, temporary);
        return *this;
    }

    bool Full() const noexcept {
        return size_ == SIZE;
    }

    bool Empty() const noexcept {
        return size_ == 0;
    }

    std::size_t Size() const noexcept {
        return size_;
    }

    void Push(const T& value) {
        if (Full()) {
            throw std::runtime_error("No place to push into the stack");
        }

        arr_[size_++] = value;
    }

    void Push(T&& value) {
        if (Full()) {
            throw std::runtime_error("No place to push into the stack");
        }

        arr_[size_++] = std::move(value);
    }


    T& Pop() {
        if (Empty()) {
            throw std::runtime_error("No elements to pop from the stack");
        }

        return arr_[--size_];
    }

    T& Top() {
        if (Empty()) {
            throw std::runtime_error("No top element in the empty stack");
        }

        return arr_[size_ - 1];
    }

    T Top() const {
        if (Empty()) {
            throw std::runtime_error("No top element in the empty stack");
        }

        return arr_[size_ - 1];      
    }
};

