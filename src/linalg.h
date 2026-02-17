#pragma once


#include <vector>
#include <iostream>
#include <map>
#include <random>

#include "polynomial.h"
#include "utils.h"

class NumericMatrix;  // Forward declaration
class UniMatrix;

class UniMatrix {
public:
    int rows, cols;
    int d = -1;
    std::vector<std::vector<UniPolynom>> matrix;
    std::vector<std::vector<int>> degree_matrix;

    // Constructor
    UniMatrix(int r, int c);

    // Accessories
    std::vector<UniPolynom>& operator[](int i) {return matrix[i];}
    std::vector<UniPolynom> operator[](int i) const {return matrix[i];}
    NumericMatrix operator()(float x) const;

    // Member functions
    UniPolynom trace();
    UniMatrix submatrix(int skip_r, int skip_c) const;
    UniPolynom det2x2() const;
    void print();
    void buildDegreeMat();
    int degree();

private:
    void _check_square() const;
};


// Numerical Matrix Class
class NumericMatrix {
    public:
    int rows, cols;
    std::vector<std::vector<double>> matrix;
    NumericMatrix(int r, int c);
    
    NumericMatrix submatrix(int skip_r, int skip_c) const;
    double det2x2() const;
    
    private:
    void _check_square() const;
    
};


// Linear Algebra Operations
UniPolynom determinant(const UniMatrix& M);
UniPolynom cofactor(const UniMatrix& M, int row, int col);
double determinant(const NumericMatrix& M);
double cofactor(const NumericMatrix& M, int row, int col);

UniPolynom newtonInterpolation(const std::vector<double>& X, const std::vector<double>& Y);

// DCEI Determinants
UniPolynom dceiDet(UniMatrix M);
UniPolynom dceiComplexDet(UniMatrix M);