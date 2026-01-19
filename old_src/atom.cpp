#include "atom.h"

// Constructors
Atom::Atom() : coeff(0), exp(0), var('x') {}

Atom::Atom(float a, char v, float e) : coeff(a), exp(e), var(v) {}

// Member function implementations
float Atom::operator()(float x) const {
    return this->coeff * std::pow(x, exp);
}

Atom Atom::operator/(float b) const {
    return Atom(this->coeff / b, this->var, this->exp);
}

Atom Atom::operator*(float b) const {
    return Atom(this->coeff * b, this->var, this->exp);
}

bool Atom::operator==(const Atom& b) const {
    if (this->coeff != b.coeff) {
        return false;
    }

    if (this->var != b.var) {
        return false;
    }

    if (this->exp != b.exp) {
        return false;
    }

    return true;
}

// Free function implementations
Atom operator/(float a, const Atom& b) {
    float coeff = a / b.coeff;
    float exp = -b.exp;

    return Atom(coeff, b.var, exp);
}

Atom operator*(float a, const Atom& b) {
    float coeff = a * b.coeff;
    return Atom(coeff, b.var, b.exp);
}
