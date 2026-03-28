#pragma once


#include <vector>
#include <iostream>
#include <map>
#include <random>
#include <complex>

#include "polynomial.h"
#include "utils.h"

// Forward declaration
class NumericMatrix;
class ComplexMatrix;
class UniMatrix;
class MultMatrix;

class UniMatrix {
public:
    int rows, cols;
    std::vector<int> shape() const;
    int d = -1;
    std::vector<std::vector<UniPolynom>> matrix;
    std::vector<std::vector<int>> degree_matrix;

    // Constructor
    UniMatrix(int r, int c);
    UniMatrix(const MultMatrix& M);

    // Accessories
    std::vector<UniPolynom>& operator[](int i) {return matrix[i];}
    std::vector<UniPolynom> operator[](int i) const {return matrix[i];}
    NumericMatrix operator()(float x) const;
    ComplexMatrix operator()(std::complex<double> x) const;

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

class MultMatrix {
public:
    int rows, cols;
    int d = -1;
    std::vector<std::vector<MultPolynom>> matrix;
    std::vector<std::vector<int>> degree_matrix;

    std::vector<int> shape() const;

    // Constructor
    MultMatrix(int r, int c);                           // OLD - keep for compatibility (creates 1-var, deg-0 polys)
    MultMatrix(int r, int c, int vars, int degree);     // NEW - recommended (all cells same structure)

    // Accessories
    std::vector<MultPolynom>& operator[](int i) {return matrix[i];}
    std::vector<MultPolynom> operator[](int i) const {return matrix[i];}
    NumericMatrix operator()(std::vector<float> vals) const;
    ComplexMatrix operator()(std::vector<std::complex<double>> vals) const;

    // Member functions
    MultPolynom trace();
    MultMatrix submatrix(int skip_r, int skip_c) const;
    MultPolynom det2x2() const;
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
    std::vector<int> shape() const;
    std::vector<std::vector<double>> matrix;
    NumericMatrix(int r, int c);
    
    std::vector<double>& operator[](int i) {return matrix[i];}
    std::vector<double> operator[](int i) const {return matrix[i];}

    NumericMatrix submatrix(int skip_r, int skip_c) const;
    double det2x2() const;
    void print() const;
    
    private:
    void _check_square() const;
    
};

// Complex Matrix Class
class ComplexMatrix {
    public:
    int rows, cols;
    std::vector<int> shape() const;
    std::vector<std::vector<std::complex<double>>> matrix;
    ComplexMatrix(int r, int c);
    
    ComplexMatrix submatrix(int skip_r, int skip_c) const;
    std::complex<double> det2x2() const;
    
    private:
    void _check_square() const;
    
};

// Linear Algebra Operations
UniPolynom determinant(const UniMatrix& M);
UniPolynom cofactor(const UniMatrix& M, int row, int col);
MultPolynom determinant(const MultMatrix& M);
MultPolynom cofactor(const MultMatrix& M, int row, int col);
double determinant(const NumericMatrix& M);
double determinantLU(const NumericMatrix& M);
double cofactor(const NumericMatrix& M, int row, int col);
std::complex<double> determinant(const ComplexMatrix& M);
std::complex<double> determinantLU(const ComplexMatrix& M);
std::complex<double> cofactor(const ComplexMatrix& M, int row, int col);

UniPolynom newtonInterpolation(const std::vector<double>& X, const std::vector<double>& Y);
UniPolynom newtonInterpolationComplex(const std::vector<std::complex<double>>& X, std::vector<std::complex<double>>& Y);

// DCEI Determinants
UniPolynom dceiDet(UniMatrix M);
UniPolynom dceiComplexDet(UniMatrix M);
UniPolynom dceiComplexDet(MultMatrix M);

// Sylvester Matrix
NumericMatrix sylvesterMat(const UniPolynom& F, const UniPolynom& G);
MultMatrix sylvesterMat(const MultPolynom& F, const MultPolynom& G);