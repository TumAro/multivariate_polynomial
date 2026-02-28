#include "polynomial.h"

// constructors
MultPolynom::MultPolynom(int vars, int degree) : vars(vars), deg(degree) {
    coeffs.resize(pow((degree+1), vars));
}

void MultPolynom::set(std::vector<double> coeff_vec) {
    int size = min((int)coeff_vec.size(), (int)this->coeffs.size());

    this->coeffs.assign(this->coeffs.size(), 0.0f);
    for (int i = 0; i < size; i++) {
        this->coeffs[i] = coeff_vec[i];
    }
}


// PRIVATE FUNCTIONS ==========================


// MEMBER FUNCTIONS ===========================

// get total degree of the polynom
int MultPolynom::degree() const {
    return this->deg;
}

void MultPolynom::print() const {
    std::cout << "(" << vars << "," << deg << ") - {";
    for (const float& val : coeffs) {
        std::cout << val << " ";
    }
    std::cout << "}" << std::endl;
}

void MultPolynom::expPrint() const {
    for (int idx = 0; idx < (int)coeffs.size(); idx++) {
        std::vector<int> exp = index2exp(idx);
        std::cout << "[";
        for (int i = 0; i < (int)exp.size(); i++) {
            if (i > 0) std::cout << ",";
            std::cout << exp[i];
        }
        std::cout << "]: " << coeffs[idx] << std::endl;
    }
}

// index to exp 
std::vector<int> MultPolynom::index2exp(int idx) const {
    std::vector<int> indices(this->vars);

    int base = this->deg+1;
    for (int i = 0; i < this->vars; i++) {
        indices[i] = (idx / (int)pow(base, i)) % base;
    }

    return indices;
}

float& MultPolynom::operator[](std::vector<int> exp) {
    int idx = 0;
    if (exp.size() != vars) {
            throw std::out_of_range("variable count do not match");
        }
    for (int i = 0; i < exp.size(); i++) {
        if (exp[i] < 0 || exp[i] > deg) {
            throw std::out_of_range("exponent exceeds degree");
        }
        idx += exp[i] * pow(deg+1, i);
    }

    return coeffs[idx];
}

float MultPolynom::operator[](std::vector<int> exp) const {
    int idx = 0;
    if (exp.size() != vars) return 0.0;
    for (int i = 0; i < exp.size(); i++) {
        if (exp[i] < 0 || exp[i] > deg) return 0.0;
        idx += exp[i] * pow(deg+1, i);
    }

    return coeffs[idx];
}
 

// ALGEBRAIC OPERATORS
MultPolynom MultPolynom::operator+(const MultPolynom& P2) const {
    int vars = max(this->vars, P2.vars);
    int deg = max(this->deg, P2.degree());

    MultPolynom result = MultPolynom(vars, deg);

    for (int idx = 0; idx < result.coeffs.size(); idx++) {
        std::vector<int> exp = result.index2exp(idx);
        result.coeffs[idx] = (*this)[exp] + P2[exp];
    }

    return result;
}

MultPolynom MultPolynom::operator+(float a) const {
    MultPolynom result = (*this);
    result.coeffs[0] = result.coeffs[0] + a;
    return result;
}

MultPolynom MultPolynom::operator-() const {
    MultPolynom result(this->vars, this->deg);

    for (int i = 0; i < result.coeffs.size(); i++) {
        result.coeffs[i] = -1*this->coeffs[i];
    }

    return result;
}

MultPolynom MultPolynom::operator-(const MultPolynom& P2) const {
    MultPolynom sub = -P2;
    MultPolynom result = (*this) + sub;

    return result;
}

MultPolynom MultPolynom::operator-(float a) const {
    MultPolynom result = (*this);
    result.coeffs[0] = result.coeffs[0] - a;
    return result;
}

MultPolynom MultPolynom::operator*(float a) const {
    MultPolynom result(this->vars, this->deg);

    for (int i = 0; i < result.coeffs.size(); i++) {
        result.coeffs[i] = this->coeffs[i]*a;
    }

    return result;
}

MultPolynom MultPolynom::operator*(const MultPolynom& P2) const {
    int vars = max(this->vars, P2.vars);
    int deg = this->deg + P2.degree();
    MultPolynom result(vars, deg);

    for (int i = 0; i < this->coeffs.size(); i++) {
        std::vector<int> exp_a = (*this).index2exp(i);
        
        for (int j = 0; j < P2.coeffs.size(); j++) {
            std::vector<int> exp_b = P2.index2exp(j);

            std::vector<int> exp_c = vecAdd(exp_a, exp_b);
            exp_c.resize(vars);
            result[exp_c] += this->coeffs[i] * P2.coeffs[j];
        }
    }

    return result;
}

//  ==================================
//  FREE FUNCTIONS
//  ==================================
MultPolynom operator+(float f, const MultPolynom& P2) {
    return P2 + f;
}

MultPolynom operator-(float f, const MultPolynom& P2) {
    MultPolynom sub = -P2;
    return sub + f;
}

MultPolynom operator*(float f, const MultPolynom& P2) {
    return P2 * f;
}