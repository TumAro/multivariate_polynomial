#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include "polynomial.h"

class PolynomialMatrix {
    public:
    int rows, cols;

    std::vector<std::vector<Polynomial>> matrix;

    PolynomialMatrix(int r, int c) : rows(r), cols(c) {
        matrix.resize(r, std::vector<Polynomial>(c));
    }

    // * get and set methods with M[i][j]
    // for modifying
    std::vector<Polynomial>& operator[](int i) {
        return matrix[i];
    }

    // for reading
    const std::vector<Polynomial>& operator[](int i) const {
        return matrix[i];
    }

    // finding trace
    Polynomial trace(){
        _check_square();
        Polynomial P;

        for (int i = 0; i < rows; i++) {
            P = P + matrix[i][i];
        }
        return P;
    }

    // submatrix
    PolynomialMatrix submatrix(int skip_r, int skip_c) const {
        PolynomialMatrix sub(rows-1, cols-1);

        int sub_i = 0;
        for (int i = 0; i < rows; i++) {
            if (i == skip_r) continue;

            int sub_j = 0;
            for (int j = 0; j < cols; j++) {
                if (j == skip_c) continue;

                sub[sub_i][sub_j] = matrix[i][j];
                sub_j++;
            }
            sub_i++;
        }
        return sub;
    }

    const Polynomial det2x2() const {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    private:
    void _check_square() const {
        if (rows != cols) {
            throw std::runtime_error(
                "Matrix must be square, given shape: (" +
                std::to_string(rows) + "x" + std::to_string(cols) + ")."
            );
        }
    }
};

#endif