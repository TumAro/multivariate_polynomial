#include "polynomial.h"

// constructors
UniPolynom::UniPolynom() : coeffs({0}) {}
UniPolynom::UniPolynom(int n) { coeffs.resize(n); }
UniPolynom::UniPolynom(std::vector<float> c) : coeffs(std::move(c)) {}

// get degree
int UniPolynom::degree() const {
    for (int i = coeffs.size() - 1; i >=0; i--) {
        if (coeffs[i] != 0.0) {
            return i;
        }
    }
    return 0;
}

// show the polynom
void UniPolynom::print() {
    std::cout << (*this).degree() << " - {";
    for (const float& val : coeffs) {
        std::cout << val << " ";
    }

    std::cout << "}" << std::endl;
}

// get coeff at an index
float UniPolynom::operator[](int n) const {
    if (n >= this->coeffs.size()) {
        return 0.00;
    }

    return this->coeffs[n];
}

float UniPolynom::operator()(float x) const {
    float result = 0;

    for (int i = 0; i < (*this).degree()+1; i++) {
        result += coeffs[i] * pow(x, i);
    }
    
    return result;
}


// Operation Addition
UniPolynom UniPolynom::operator+(const UniPolynom& P2) const {
    int size = max(this->coeffs.size(), P2.coeffs.size());
    std::vector<float> vec(size);

    // overlap add the elements
    for (int i = 0; i < size; i++) {
        vec[i] = (*this)[i] + P2[i]; 
    }

    return UniPolynom(vec);
}

UniPolynom UniPolynom::operator+(float a) const {
    UniPolynom P = *this;
    P.coeffs[0] = P.coeffs[0] + a;
    return P;
}


//  ==================================
//  FREE FUNCTIONS
//  ==================================
UniPolynom operator+(float f, const UniPolynom& P2) {
    return P2 + f;
}