#pragma once

#include <vector>
#include <iostream>
#include <complex>

#include "utils.h"

// forward declaration
class UniPolynom;
class MultPolynom;

class UniPolynom {
    // the actual coeff vector
    std::vector<float> coeffs;
public:
    //constructor
    UniPolynom();
    UniPolynom(int n);
    UniPolynom(std::vector<float> c);
    UniPolynom(std::initializer_list<float> c) : UniPolynom(std::vector<float>(c)) {}
    explicit UniPolynom(const MultPolynom& P); // converts MultPolynom(vars=1) to UniPolynom

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
    MultPolynom();                      // Default constructor (creates 1-var, degree-0 polynomial)
    MultPolynom(int vars, int degree);

    int degree() const;
    void set(std::vector<double> coeff_vec);
    void print() const;
    void expPrint() const;
    std::vector<int> index2exp(int idx) const;

    float operator()(std::vector<float> vals) const;
    std::complex<double> operator()(std::vector<std::complex<double>> x) const;
    float& operator[](std::vector<int> exp);
    float  operator[](std::vector<int> exp) const;
    MultPolynom coeff(std::vector<int> partial) const;
    int numVars() const { return vars; }

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
