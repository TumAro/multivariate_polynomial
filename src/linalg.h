#pragma once


#include <vector>
#include <iostream>
#include <map>

#include "polynomial.h"
#include "utils.h"

class UniMatrix {
public:
    int rows, cols;
    std::vector<std::vector<UniPolynom>> matrix;

    // Constructor
    UniMatrix(int r, int c);

    // Accessories
    std::vector<UniPolynom>& operator[](int i) {return matrix[i];}
    std::vector<UniPolynom> operator[](int i) const {return matrix[i];}

    // Member functions
    UniPolynom trace();
    UniMatrix submatrix(int skip_r, int skip_c) const;
    UniPolynom det2x2() const;
    void print();

private:
    void _check_square() const;
};

// Linear Algebra Operations
UniPolynom determinant(const UniMatrix& M);
UniPolynom cofactor(const UniMatrix& M, int row, int col);
