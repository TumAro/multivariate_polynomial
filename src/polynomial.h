#pragma once

#include <vector>
#include <iostream>

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
    void print();
    float operator[](int n) const;
    float operator()(float x) const;

    //member operators
    UniPolynom operator+(const UniPolynom& P2) const;
    UniPolynom operator+(float a) const;

    // UniPolynom operator-() const;
    // UniPolynom operator-(const UniPolynom& P2) const;
    // UniPolynom operator-(float a) const;

    // UniPolynom operator*(const UniPolynom& P2) const;
    // UniPolynom operator*(float a) const;

};

// FREE FUNCTION - Univariate Polynomial
UniPolynom operator+(float f, const UniPolynom& P2);
// UniPolynom operator-(float f, const UniPolynom& P2);
// UniPolynom operator*(float f, const UniPolynom& P2);