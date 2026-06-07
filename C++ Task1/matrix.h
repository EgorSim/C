#pragma once

#include <iostream>

class Matrix {
public:
    Matrix(int rows, int cols);
    ~Matrix();

    Matrix(const Matrix&) = delete;
    Matrix& operator=(const Matrix&) = delete;

    void input(std::istream& in = std::cin);
    void print(std::ostream& out = std::cout) const;
    void swapEvenOddColumns();

    int rows() const noexcept { return rows_; }
    int cols() const noexcept { return cols_; }

private:
    int rows_;
    int cols_;
    int** data_;
};

bool readPositiveInt(const char* prompt, int& value, std::istream& in = std::cin,
                     std::ostream& out = std::cout);
