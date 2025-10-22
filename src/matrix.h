#ifndef MATRIX_H
#define MATRIX_H

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

    Polynomial det2x2() {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
};

#endif