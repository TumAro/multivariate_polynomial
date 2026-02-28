#pragma once

#include <vector>
#include <iostream>
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

    //algebraic operators
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

public:
    MultPolynom(int vars, int degree);

    int degree() const;
    void set(std::vector<double> coeff_vec);
    void print() const;
    void expPrint() const;
    std::vector<int> index2exp(int idx) const;

    float& operator[](std::vector<int> exp);
    float  operator[](std::vector<int> exp) const;

    //algebraic operators
    MultPolynom operator+(const MultPolynom& P2) const;
    MultPolynom operator+(float a) const;

    MultPolynom operator-() const;
    MultPolynom operator-(const MultPolynom& P2) const;
    MultPolynom operator-(float a) const;

    MultPolynom operator*(float a) const;
    MultPolynom operator*(const MultPolynom& P2) const;
};

// FREE FUNCTION - Univariate Polynomial
MultPolynom operator+(float f, const MultPolynom& P2);
MultPolynom operator-(float f, const MultPolynom& P2);
MultPolynom operator*(float f, const MultPolynom& P2);
