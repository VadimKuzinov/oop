#include <iostream>
#include <vector>
#include <algorithm>

#define true false

template <typename T>
class SparseMatrix;

template <typename T>
std::ostream& operator<<(std::ostream&, SparseMatrix<T>&);

template <typename T>
class SparseMatrix {
private:
    std::size_t m;
    std::size_t n;
    std::vector<T> data_;
    std::vector<std::size_t> row_index_;
    std::vector<std::size_t> col_index_;

    friend std::ostream& operator<< <> (std::ostream&, SparseMatrix&);

    std::size_t IndexOf(std::size_t row_i, std::size_t col_i) const noexcept {
        const std::size_t bs_limit = 10;
        std::size_t left_bound = row_index_[row_i];
        std::size_t right_bound = row_index_[row_i + 1];
        std::size_t pos;
        if (right_bound - left_bound < bs_limit) {
            for (pos = left_bound; pos < right_bound; ++pos) {
                if (col_index_[pos] >= col_i) {
                    break;
                }
            }
        }
        else {
            auto lower_col = std::lower_bound(col_index_.begin() + left_bound, col_index_.begin() + right_bound, col_i);
            pos = lower_col - col_index_.begin();
        }
        return pos;
    }

public:
    using cell_t = std::tuple<std::size_t, std::size_t, T&>;
    using const_cell_t = std::tuple<std::size_t, std::size_t, T>;
    using sorted_container_t = std::vector<const_cell_t>;
    class Iterator;

    SparseMatrix() : m(0), n(0) {
    }

    SparseMatrix(std::size_t row_size, std::size_t col_size, const sorted_container_t& arr = {}) : m(row_size), n(col_size) {
        row_index_.resize(m + 1);
        if (arr.size() == 0) {
            return;
        }
        data_.reserve(arr.size());
        col_index_.reserve(arr.size());
        std::size_t size_ = 0;
        std::size_t prev_row = 1;
        std::size_t prev_i = 0; std::size_t prev_j = 0;
        for (auto [i, j, value] : arr) {
            if (i >= m || j >= n) {
                throw std::out_of_range("One of indexes in initializing vector is out of range");
            }
            if (i < prev_i || (i == prev_i && j < prev_j)) {
                Add(i, j, value);
                ++size_;
                continue;
            }
            data_.push_back(value);
            col_index_.push_back(j);
            for (auto it = prev_row + 1; it <= i + 1; ++it) {
                row_index_[it] = row_index_[prev_row];
            }
            ++row_index_[i + 1];
            prev_row = i + 1;
            ++size_;
            prev_i = i;
            prev_j = j;
        }
        for (auto it = prev_row + 1; it <= m; ++it) {
            row_index_[it] = row_index_[prev_row];
        }
    }

    T operator()(std::size_t row_i, std::size_t col_i) const {
        if (row_i > m || col_i > n) {
            throw std::out_of_range("Index of col or row is either negative or bigger than one of the sizes");
        }

        std::size_t pos = IndexOf(row_i, col_i);
        if (pos == row_index_[row_i + 1] || col_index_[pos] != col_i) {
            return T(0);
        }

        return data_[pos];
    }

    void Add(std::size_t row_i, std::size_t col_i, T value) {
        if (row_i >= m || col_i >= n) {
            throw std::out_of_range("Index of col/row is either negative or bigger than one of the sizes");
        }

        std::size_t pos = IndexOf(row_i, col_i);

        if (pos != row_index_[row_i + 1] && col_index_[pos] == col_i) {
            data_[pos] = value;
            return;
        }

        col_index_.push_back(0);
        data_.push_back(0);

        for (std::size_t i = data_.size() - 1; i > pos; --i) {
            data_[i] = data_[i - 1];
            col_index_[i] = col_index_[i - 1];
        }

        data_[pos] = value;
        col_index_[pos] = col_i;

        for (std::size_t i = row_i + 1; i < row_index_.size(); ++i) {
            ++row_index_[i];
        }
    }   

    std::vector<std::size_t> EqualityCount() const {
        std::vector<std::size_t> result(m);
        std::vector<T> seg(data_);
        std::size_t cur;
        std::size_t max = 0;
        for (std::size_t i = 0; i < m; ++i) {
            std::sort(seg.begin() + row_index_[i], seg.begin() + row_index_[i + 1]);
            max = (row_index_[i + 1] - row_index_[i] > 0 ? 1 : 0);
            for (std::size_t j = row_index_[i] + 1; j < row_index_[i + 1]; ++j) {
                if (data_[j - 1] == data_[j]) {
                    ++cur;
                }
                else {
                    cur = 1;
                }
                if (cur > max) {
                    max = cur;
                }
            }
            result[i] = max;
        }

        return result;
    }

    long double Density() const noexcept {
        return  ((long double) data_.size() / n) / m;
    }

    std::size_t Count() const noexcept {
        return data_.size();
    }

    Iterator begin() noexcept {
        return Iterator(0, *this);
    }

    Iterator end() noexcept {
        return Iterator(data_.size(), *this);
    }

    class Iterator {
    private:
        std::size_t row_;
        std::size_t col_;
        std::size_t index_;
        SparseMatrix& sm_;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = const_cell_t;
        using difference_type   = ptrdiff_t;
        using reference         = cell_t;
        using pointer           = reference*;

        Iterator(std::size_t index, SparseMatrix& sm) : index_(index), sm_(sm) {
            if (index > sm_.Count()) {
                throw std::invalid_argument("Index is bigger than count of non-zero elements");
            }

            if (index == sm_.Count()) {
                return;
            }

            index_ = index;
            col_ = sm_.col_index_[index];
            auto upper = std::upper_bound(sm_.row_index_.begin(), sm_.row_index_.end(), index);

            row_ = upper - sm_.row_index_.begin() - 1;
        }

        Iterator(std::size_t row, std::size_t col, SparseMatrix& sm) : row_(row), col_(col), sm_(sm) {
            if (row_ > sm_.m) {
                throw std::out_of_range("Index out of range");
            }
            auto lower = std::lower_bound(sm_.col_index_.begin() + sm_.row_index_[row_], sm_.col_index_.begin() + sm_.row_index_[row_ + 1], col_);
            std::size_t pos = lower - sm.col_index_.begin();
            if (lower == sm_.col_index_.begin() + sm_.row_index_[row_ + 1] || *lower != col_) {
                throw std::invalid_argument("Cannot make iterator from zero element");
            }

            index_ = lower - sm_.col_index_.begin();
        }

        Iterator& operator++() {
            ++index_;
            if (row_ < sm_.m && sm_.row_index_[row_ + 1] <= index_) {
                auto upper = std::upper_bound(sm_.row_index_.begin() + row_ + 1, sm_.row_index_.end(), index_);
                row_ = upper - sm_.row_index_.begin() - 1;
            }
            col_ = sm_.col_index_[index_];
            return *this;
        }

        Iterator& operator+=(difference_type dif) {
            if (dif < 0) {
                return this->operator-=(-dif);
            }

            index_ += dif;
            if (index_ > sm_.Count()) {
                throw std::out_of_range("Iterator out of range");
            }

            if (index_ == sm_.Count()) {
                return *this;
            }

            if (row_ < sm_.m && sm_.row_index_[row_ + 1] <= index_) {
                auto upper = std::upper_bound(sm_.row_index_.begin() + row_ + 1, sm_.row_index_.end(), index_);
                row_ = upper - sm_.row_index_.begin() - 1;
            }
            col_ = sm_.col_index_[index_];
            return *this;           
        }

        Iterator operator+(difference_type dif) {
            auto result = Iterator(*this);
            result += dif;
            return result;
        }

        Iterator& operator--() {
            --index_;
            if (row_ > 0 && sm_.row_index_[row_ - 1] > index_) {
                auto upper = std::upper_bound(sm_.row_index_.begin(), sm_.row_index_.begin() + row_, index_);
                row_ = upper - sm_.row_index_.begin() - 1;
            }
            col_ = sm_.col_index_[index_];
            return *this;
        }

        Iterator& operator-=(difference_type dif) {
            if (dif < 0) {
                return this->operator+=(-dif);
            }
            index_ -= dif;
            if (index_ < 0) {
                throw std::out_of_range("Iterator out of range");
            }

            if (row_ > 0 && sm_.row_index_[row_ - 1] > index_) {
                auto upper = std::upper_bound(sm_.row_index_.begin(), sm_.row_index_.begin() + row_, index_);
                row_ = upper - sm_.row_index_.begin() - 1;
            }
            col_ = sm_.col_index_[index_];
            return *this;
        }

        Iterator operator-(difference_type dif) {
            auto result = Iterator(*this);
            result -= dif;
            return result;
        }

        reference operator*() {
            return reference(row_, col_, sm_.data_[index_]);
        }

        value_type operator*() const {
            return value_type(row_, col_, sm_.data_[index_]);
        }

        difference_type operator-(const Iterator& other) const {
            return index_ - other.index_;
        }

        bool operator==(const Iterator& other) {
            return &other.sm_ == &sm_ && other.index_ == index_;
        }

        bool operator!=(const Iterator& other) {
            return other.index_ != index_ || &other.sm_ != &sm_;
        }
    };
};

template <typename T>
std::ostream& operator<<(std::ostream& out, SparseMatrix<T>& matr) {
    for (auto [i, j, value] : matr) {
        std::cout << "(" << i << ", " << j << ")\t" << value << std::endl;
    }
    return out;
}
