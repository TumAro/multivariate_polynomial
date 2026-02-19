#include "polynomial.h"

// constructors
UniPolynom::UniPolynom() : coeffs({0}) {}
UniPolynom::UniPolynom(int n) { coeffs.resize(n, 0.0f); }
UniPolynom::UniPolynom(std::vector<float> c) : coeffs(std::move(c)) {}

// get degree of polynom
int UniPolynom::degree() const {
    for (int i = coeffs.size() - 1; i >=0; i--) {
        if (coeffs[i] != 0.0) {
            return i;
        }
    }
    return 0;
}

// get leading coefficient
float UniPolynom::lead() const {
    int index = (*this).degree();
    return this->coeffs[index];
}

// get the intercept or the constant term
float UniPolynom::intercept() const {
    return this->coeffs[0];
}

// show the polynom
void UniPolynom::print() {
    std::cout << (*this).degree() << " - {";
    for (const float& val : coeffs) {
        std::cout << val << " ";
    }

    std::cout << "}";
}

// get coeff at an index
float& UniPolynom::operator[](int n) {
    return coeffs[n];  // Let it crash if out of bounds
}

float UniPolynom::operator[](int n) const {
    if (n >= this->coeffs.size()) {
        return 0.00;
    }

    return this->coeffs[n];
}

// evaluate at value of variable
float UniPolynom::operator()(float x) const {
    float result = 0;

    for (int i = 0; i < (*this).degree()+1; i++) {
        result += coeffs[i] * pow(x, i);
    }
    
    return result;
}

std::complex<double> UniPolynom::operator()(std::complex<double> x) const {
    std::complex<double> result = 0;

    for (int i = 0; i < (*this).degree()+1; i++) {
        result += (double)coeffs[i] * pow(x, i);
    }
    
    return result;
}

// setter
UniPolynom& UniPolynom::operator=(const std::vector<float>& vect) {
    this->coeffs = vect;
    return *this;
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

// Operation Negetion
UniPolynom UniPolynom::operator-() const {
    int size = (*this).degree()+1;
    UniPolynom P(size);

    for (int i = 0 ; i < size; i++) {
        P.coeffs[i] = -(this->coeffs[i]);
    }

    return P;
}

// Operation Substraction
UniPolynom UniPolynom::operator-(const UniPolynom& P2) const {
    UniPolynom sub = -P2;
    return (*this) + sub;
}

UniPolynom UniPolynom::operator-(float a) const {
    return (*this) + (-a);
}

UniPolynom UniPolynom::operator*(float a) const {
    int size = (*this).degree()+1;
    UniPolynom result(size);

    for (int i = 0; i < size; i++) {
        result.coeffs[i] = a*(this->coeffs[i]);
    }

    return result;
}

UniPolynom UniPolynom::operator*(const UniPolynom& other) const {
    /*
    For i in (0 to P.size-1):
        coeff = P[i]
        zeroes = {0}*(i)

        temp[i] = coeff * {zeroes, Q}

    return SUM(temp for all i)
    */
    bool smaller = (*this).degree() < other.degree();
    UniPolynom P = (smaller) ? (*this) : other;
    UniPolynom Q = (!smaller) ? (*this) : other;

    UniPolynom result(P.degree()+ Q.degree()+1);

    result = result + P[0]*Q;
    for (int i = 1; i < P.degree()+1; i++) {
        float coeff = P[i];
        std::vector<float> joinedVector = joinVectors(std::vector<float>(i), Q.coeffs);
        UniPolynom joinedPoly(joinedVector);

        result = result + coeff*joinedPoly;
    }
    return result;
}


//  ==================================
//  FREE FUNCTIONS
//  ==================================
UniPolynom operator+(float f, const UniPolynom& P2) {
    return P2 + f;
}

UniPolynom operator-(float f, const UniPolynom& P2) {
    return -P2 + f;
}

UniPolynom operator*(float f, const UniPolynom& P2) {
    return P2 * f;
}