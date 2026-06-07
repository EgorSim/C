#include "matrix.h"

#include <climits>
#include <iomanip>
#include <limits>
#include <new>
#include <stdexcept>

namespace {

int digitCount(int value) {
    if (value == 0) {
        return 1;
    }

    int count = 0;
    long long n = value;
    if (n < 0) {
        n = -n;
        count = 1;
    }

    while (n > 0) {
        n /= 10;
        ++count;
    }
    return count;
}

void clearStream(std::istream& in) {
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

}  // namespace

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols), data_(nullptr) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Размерность матрицы должна быть положительной.");
    }

    data_ = new (std::nothrow) int*[rows_];
    if (data_ == nullptr) {
        throw std::bad_alloc();
    }

    for (int i = 0; i < rows_; ++i) {
        data_[i] = new (std::nothrow) int[cols_];
        if (data_[i] == nullptr) {
            for (int j = 0; j < i; ++j) {
                delete[] data_[j];
            }
            delete[] data_;
            data_ = nullptr;
            throw std::bad_alloc();
        }
    }
}

Matrix::~Matrix() {
    if (data_ == nullptr) {
        return;
    }

    for (int i = 0; i < rows_; ++i) {
        delete[] data_[i];
    }
    delete[] data_;
}

void Matrix::input(std::istream& in) {
    std::cout << "Введите элементы матрицы (" << rows_ << " x " << cols_ << "):\n";

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            while (true) {
                std::cout << "A[" << i << "][" << j << "] = ";
                if (in >> data_[i][j]) {
                    break;
                }

                std::cerr << "Ошибка: введите целое число.\n";
                clearStream(in);
            }
        }
    }
}

void Matrix::print(std::ostream& out) const {
    int maxWidth = 1;
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            maxWidth = std::max(maxWidth, digitCount(data_[i][j]));
        }
    }

    const int cellWidth = maxWidth + 2;

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            out << std::setw(cellWidth) << data_[i][j];
        }
        out << '\n';
    }
}

void Matrix::swapEvenOddColumns() {
    for (int col = 0; col + 1 < cols_; col += 2) {
        for (int row = 0; row < rows_; ++row) {
            int temp = data_[row][col];
            data_[row][col] = data_[row][col + 1];
            data_[row][col + 1] = temp;
        }
    }
}

bool readPositiveInt(const char* prompt, int& value, std::istream& in, std::ostream& out) {
    while (true) {
        out << prompt;
        if (!(in >> value)) {
            std::cerr << "Ошибка: введите целое число.\n";
            clearStream(in);
            continue;
        }

        if (value <= 0) {
            std::cerr << "Ошибка: значение должно быть больше нуля.\n";
            clearStream(in);
            continue;
        }

        if (value > INT_MAX / 1000) {
            std::cerr << "Ошибка: слишком большое значение.\n";
            clearStream(in);
            continue;
        }

        return true;
    }
}
