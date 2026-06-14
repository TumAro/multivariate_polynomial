#include "polynomial.h"

// Default constructor - creates minimal valid polynomial (1 var, degree 0)
MultPolynom::MultPolynom() : vars(1), deg(0) {
    coeffs.resize(1, 0.0f);  // Single coefficient initialized to 0
}

// constructors
MultPolynom::MultPolynom(int vars, int degree) : vars(vars), deg(degree) {
    coeffs.resize(binomial(degree+vars, vars), 0.0f);
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
    std::cout << "{";
    for (const float& val : coeffs) std::cout << val << " ";
    std::cout << "}";
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

// evaluate
float MultPolynom::operator()(std::vector<float> vals) const {
    if ((int)vals.size() != this->vars) {
        std::cerr << "Invalid input vector size. SIZE: " << this->vars
                  << ", GIVEN: " << vals.size() << std::endl;
        return 0.0f;
    }

    float result = this->coeffs[0];

    for (size_t i = 1; i < this->coeffs.size(); i++) {
        if (this->coeffs[i] == 0) continue;  // Early skip

        float monomial = 1.0f;
        std::vector<int> exp = index2exp(i); // <- binomial decode
        
        // Decode exponents on-the-fly without allocation
        for (int var_i = 0; var_i < this->vars; var_i++) {
            if (exp[var_i] != 0)
                monomial *= pow(vals[var_i], exp[var_i]);
        }
        
        result += monomial * this->coeffs[i];
    }

    return result;
}

std::complex<double> MultPolynom::operator()(std::vector<std::complex<double>> vals) const {
    if ((int)vals.size() != this->vars) {
        std::cerr << "Invalid input vector size. SIZE: " << this->vars
                  << ", GIVEN: " << vals.size() << std::endl;
        return std::complex<double>(0.0, 0.0);
    }

    std::complex<double> result = (double)this->coeffs[0];

    for (size_t i = 1; i < this->coeffs.size(); i++) {
        if (this->coeffs[i] == 0.0f) continue;  // Early skip

        std::complex<double> monomial = std::complex<double>(1.0, 0.0);
        std::vector<int> exp = index2exp(i); // <- binomial decode
        
        // Decode exponents on-the-fly without allocation
        for (int var_i = 0; var_i < this->vars; var_i++) {
            if (exp[var_i] != 0)
                monomial *= std::pow(vals[var_i], exp[var_i]);
        }

        result += monomial * (double)this->coeffs[i];
    }

    return result;
}

MultPolynom MultPolynom::partialEval(int var_idx, double val) const {
    MultPolynom result(vars-1,deg);
    
    for (int i = 0; i <= deg; i++) {
        result = result + coeff(var_idx, i) * (float)pow(val, i);
    }

    return result;
}

// index to exp
std::vector<int> MultPolynom::index2exp(int idx) const {
    std::vector<int> indices(this->vars, 0);
    int budget = this->deg;
    int rem = idx;

    for (int n = this->vars; n >= 2; n--) {
        int k = 0;
        while (rem >= binomial(budget - k + n - 1, n - 1)) {
            rem -= binomial(budget - k + n - 1, n - 1);
            k++;
        }
        indices[n-1] = k;
        budget -= k;
    }
    indices[0] = rem;

    return indices;
}

float& MultPolynom::operator[](std::vector<int> exp) {
    if ((int)exp.size() != vars)
        throw std::out_of_range("variable count does not match");

    int total = 0;
    for (int i = 0; i < (int)exp.size(); i++) {
        if (exp[i] < 0) throw std::out_of_range("negative exponent");
        total += exp[i];
    }
    if (total > deg) throw std::out_of_range("total exponent exceeds degree");

    int idx = 0;
    int budget = deg;
    for (int i = vars - 1; i >= 1; i--) {
        int k = exp[i];
        int n = i + 1;
        idx += binomial(budget + n, n) - binomial(budget - k + n, n);
        budget -= k;
    }
    idx += exp[0];

    return coeffs[idx];
}

MultPolynom MultPolynom::coeff(std::vector<int> partial) const {
    int fixed = partial.size();
    int remaining = vars - fixed;
    MultPolynom result(remaining > 0 ? remaining : 1, remaining > 0 ? deg : 0);

    for (int idx = 0; idx < (int)coeffs.size(); idx++) {
        auto exp = index2exp(idx);

        bool match = true;
        for (int i = 0; i < fixed; i++)
            if (exp[i] != partial[i]) { match = false; break; }
        if (!match) continue;

        std::vector<int> rem;
        for (int i = fixed; i < vars; i++)
            rem.push_back(exp[i]);

        if (rem.empty()) result.coeffs[0] = coeffs[idx];
        else             result[rem]       = coeffs[idx];
    }
    return result;
}

MultPolynom MultPolynom::coeff(int var_idx, int exponent) const {
    int remaining = vars - 1;
    MultPolynom result(remaining > 0 ? remaining : 1, remaining > 0 ? deg : 0);

    for (int idx = 0; idx < (int)coeffs.size(); idx++) {
        auto exp = index2exp(idx);

        if (exp[var_idx] != exponent) continue;

        std::vector<int> rem;
        for (int i = 0; i < vars; i++)
            if (i != var_idx)
                rem.push_back(exp[i]);

        if (rem.empty()) result.coeffs[0] = coeffs[idx];
        else             result[rem]       = coeffs[idx];
    }
    return result;
}

float MultPolynom::operator[](std::vector<int> exp) const {
    if ((int)exp.size() > vars) {
        for (int i = vars; i < (int)exp.size(); i++)
            if (exp[i] != 0) return 0.0f;
        exp.resize(vars);
    }
    if ((int)exp.size() != vars) return 0.0f;

    int total = 0;
    for (int i = 0; i < (int)exp.size(); i++) {
        if (exp[i] < 0) return 0.0f;
        total += exp[i];
    }
    if (total > deg) return 0.0f;

    int idx = 0;
    int budget = deg;
    for (int i = vars - 1; i >= 1; i--) {
        int k = exp[i];
        int n = i + 1;
        idx += binomial(budget + n, n) - binomial(budget - k + n, n);
        budget -= k;
    }
    idx += exp[0];

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
