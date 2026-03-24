#pragma once

#include "array/vector.hpp"
#include <stdexcept>

namespace dsac::array {

    class Matrix {
    private:
        int rows{ 0 };
        int cols{ 0 };
        dsac::array::Vector<dsac::array::Vector<int>> data;

    public:
        Matrix(int r, int c) {
            if (r < 0 || c < 0) {
                throw std::out_of_range("Negative dimensions");
            }

            rows = r;
            cols = c;

            for (int i = 0; i < rows; ++i) {
                dsac::array::Vector<int> row;
                for (int j = 0; j < cols; ++j) {
                    row.push_back(0);
                }
                data.push_back(row);
            }
        }

        int& operator()(int i, int j) {
            return data.at(i).at(j);
        }

        Matrix operator+(Matrix& other) {
            if (rows != other.rows || cols != other.cols) {
                throw std::out_of_range("dimensions must match");
            }

            Matrix result(rows, cols);

            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    result(i, j) = (*this)(i, j) + other(i, j);
                }
            }

            return result;
        }
    };

}