#include "polynomial.h"

// constructors
MultPolynom::MultPolynom(int vars, int degree) : vars(vars), deg(degree) {this->setupIndices();}


// PRIVATE FUNCTIONS ==========================
void MultPolynom::setupIndices() {
    this->exp_table = lexorderArray(this->deg, this->vars);

    // int size = factorial(vars + degree - 1) / ( factorial(vars-1) * factorial(degree) );
    int size = this->exp_table.size();
    this->coeffs.resize(size);

    for (int i = 0; i < size; i++) {
        exp_map[exp_table[i]] = i;
    }
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

float& MultPolynom::operator[](std::vector<int> exp) {
    return this->coeffs[this->exp2index(exp)];
}

float MultPolynom::operator[](std::vector<int> exp) const {
    return this->coeffs[this->exp2index(exp)];
}

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