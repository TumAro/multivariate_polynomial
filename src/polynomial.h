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
    float lead() const;
    float intercept() const;
    void print();
    float operator[](int n);    // modifiable
    float operator[](int n) const;
    float operator()(float x) const;

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
    static int vars;
    static std::vector<int> degrees;

public:
    MultPolynom(int var, std::vector<int>& degrees);
}