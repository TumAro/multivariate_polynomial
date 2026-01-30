#include "polynomial.h"

// constructors
MultPolynom::MultPolynom(int vars, int degree) : vars(vars), deg(degree) {this->setupIndices();}


// PRIVATE FUNCTIONS ==========================

// GENERATING INDICES UPTO and NOT FOR ONLY
void MultPolynom::setupIndices() {
    // // int size = factorial(vars + degree - 1) / ( factorial(vars-1) * factorial(degree) );
    
    // generate all monomials from degree 0 to deg
    for (int d = 0; d <= this->deg; d++) {
        auto terms = lexorderArray(d, this->vars);
        exp_table.insert(exp_table.end(), terms.begin(), terms.end());
    }


    // this->exp_table = lexorderArray(this->deg, this->vars);
    // int size = this->exp_table.size();
    // this->coeffs.resize(size);

    for (int i = 0; i <  exp_table.size(); i++) {
        exp_map[exp_table[i]] = i;
    }

    coeffs.resize(exp_table.size());
}

// MEMBER FUNCTIONS ===========================

// get total degree of the polynom
int MultPolynom::degree() const {
    return this->deg;
}

// show the polynom
void MultPolynom::print() const {
    std::cout << (*this).degree() << " - {";
    for (const float& val : coeffs) {
        std::cout << val << " ";
    }

    std::cout << "}" << std::endl;
}

// show the exponent map
void MultPolynom::expPrint() const {
    std::cout << "Generated sequences:" << std::endl;
    for (auto& seq : this->exp_table) {
        std::cout << "(";
        for (int i = 0; i < seq.size(); i++) {
            std::cout << seq[i];
            if (i < seq.size() - 1) std::cout << ", ";
        }
        std::cout << "), ";
    }
    std::cout << std::endl;
}

// index to exponent
std::vector<int> MultPolynom::index2exp(int idx) const {
    return exp_table[idx];
}

// exponent to index
int MultPolynom::exp2index(std::vector<int> exp) const {
    return exp_map.at(exp);
}

float MultPolynom::operator[](std::vector<int> exp) const {

    std::vector<int> padded = exp;
    padded.resize(this->vars, 0);

    auto it = exp_map.find(padded);
    if (it == exp_map.end()) {
        return 0.0;
    }

    return coeffs[it->second];
    // return this->coeffs[this->exp2index(exp)];
}
float& MultPolynom::operator[](std::vector<int> exp) {
    auto it = exp_map.find(exp);
    if (it == exp_map.end()) {
        throw std::out_of_range("exponent not in polynom struct");
    }

    return coeffs[it->second];

    // return this->coeffs[this->exp2index(exp)];
}

// setter
MultPolynom& MultPolynom::operator=(std::vector<float> vect) {
if ( vect.size() > coeffs.size()) {
        std::cerr << "Error: size mismatch. Vector of size " << vect.size() << " provided for a " << coeffs.size() << " sized polynomial." << std::endl;
        return *this;
    }

    // Copy provided values
    for (int i = 0; i < vect.size(); i++) {
        coeffs[i] = vect[i];
    }
    
    // Pad rest with zeros
    for (int i = vect.size(); i < coeffs.size(); i++) {
        coeffs[i] = 0.0;
    }

    return *this;
}

// ALGEBRAIC OPERATORS

MultPolynom MultPolynom::operator+(const MultPolynom& P2) const {
    int vars = max(this->vars, P2.vars);
    int deg = max(this->deg, P2.deg);

    MultPolynom P(vars, deg);

    for (int i = 0; i < P.coeffs.size(); i++) {
        auto exp = P.index2exp(i);
        P.coeffs[i] = (*this)[exp] + P2[exp];
    }

    return P;
}

MultPolynom MultPolynom::operator+(float a) const {
    MultPolynom P = *this;
    std::vector<int> zero(this->vars, 0);
    P[zero] += a;
    return P;
}