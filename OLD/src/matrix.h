#pragma once

#include <stdexcept>
#include "polynomial.h"

class PolynomialMatrix {
public:
    int rows, cols;
    std::vector<std::vector<Polynomial>> matrix;

    // Constructor
    PolynomialMatrix(int r, int c);

    // Accessor operators - can stay inline (simple return)
    std::vector<Polynomial>& operator[](int i) {
        return matrix[i];
    }

    const std::vector<Polynomial>& operator[](int i) const {
        return matrix[i];
    }

    // Member function declarations
    Polynomial trace();
    PolynomialMatrix submatrix(int skip_r, int skip_c) const;
    const Polynomial det2x2() const;
    void print();

    // Operator overloads
    PolynomialMatrix operator*(const PolynomialMatrix& N) const;
    PolynomialMatrix operator*(const Polynomial& a) const;
    PolynomialMatrix operator^(const int& n) const;

private:
    void _check_square() const;
};

// Free function declaration
PolynomialMatrix operator*(const Polynomial& a, const PolynomialMatrix& M);
