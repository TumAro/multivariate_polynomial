#pragma once

#include <vector>
#include <iostream>
#include <map>
#include <complex>

#include "utils.h"

class UniPolynom {
    // the actual coeff vector
    std::vector<float> coeffs;
public:
    //constructor
    UniPolynom();
    UniPolynom(int n);
    UniPolynom(std::vector<float> c);

    //member functions
    int degree() const;
    float lead() const;
    float intercept() const;
    void print();
    float& operator[](int n);    // modifiable
    float operator[](int n) const;
    float operator()(float x) const;
    std::complex<double> operator()(std::complex<double> x) const;

    UniPolynom& operator=(const std::vector<float>& vect);

    //member operators
    UniPolynom operator+(const UniPolynom& P2) const;
    UniPolynom operator+(float a) const;

    UniPolynom operator-() const;
    UniPolynom operator-(const UniPolynom& P2) const;
    UniPolynom operator-(float a) const;

    UniPolynom operator*(float a) const;
    UniPolynom operator*(const UniPolynom& P2) const;

};

// FREE FUNCTION - Univariate Polynomial
UniPolynom operator+(float f, const UniPolynom& P2);
UniPolynom operator-(float f, const UniPolynom& P2);
UniPolynom operator*(float f, const UniPolynom& P2);


class MultPolynom {
    std::vector<float> coeffs;
    int vars;
    int deg;

    std::vector<std::vector<int>> exp_table;  // index -> exponents
    std::map<std::vector<int>, int> exp_map;  // exponents -> index

    public:
    MultPolynom(int vars, int degree);
    
    //member operators
    int degree() const;
    void print() const;
    void expPrint() const;
    
    std::vector<int> index2exp(int idx) const;
    int exp2index(std::vector<int> exp) const;
    
    // indexing and evaluation
    float& operator[](std::vector<int> exp);    // modifiable
    float operator[](std::vector<int> exp) const;
    float operator()(float x_val, float y_val, ...) const;
    
    MultPolynom& operator=(std::vector<float> vect);
    
    // algebraic operators
    MultPolynom operator+(const MultPolynom& P2) const;
    MultPolynom operator+(float a) const;
    
    MultPolynom operator-() const;
    MultPolynom operator-(const MultPolynom& P2) const;
    MultPolynom operator-(float a) const;
    
    MultPolynom operator*(const MultPolynom& P2) const;
    MultPolynom operator*(float a) const;
    
    private:
           // Creates exp -> index map
           void setupIndices();
};

// FREE FUNCTION - Multivariate Polynomial
// MultPolynom operator+(float f, const UniPolynom& P2);
// MultPolynom operator-(float f, const UniPolynom& P2);
// MultPolynom operator*(float f, const UniPolynom& P2);


