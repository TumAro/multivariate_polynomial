#include <cmath>
#include <stdexcept>

class Atom {
    public:
        float coeff;
        float exp;
        char var;

        Atom() : coeff(0), exp(0), var('x') {}
        Atom(float a, char v, float e) : coeff(a), exp(e), var(v) {}

        float getCoeff() const {
            return coeff;
        }

        float operator()(float x) const {
            return this->coeff * std::pow(x, exp);
        }

        // * Overload / operator, A = a / b
        // Atom operator/(const Atom& b) {
        //     float coeff = this->coeff / b.coeff;
        //     float exp = this->exp - b.exp;

        //     if (this->var == b.var) {
        //         return Atom(coeff, this->var, exp);
        //     }
        //     return Atom();
        // }

        Atom operator/(float b) {
            return Atom(this->coeff / b, this->var, this->exp);
        }

        // * Overload == operator (a == b)
        bool operator==(const Atom& b) {
            if (this->coeff != b.coeff) {
                return false;
            }

            if (this->var!= b.var) {
                return false;
            }

            if (this->exp != b.exp) {
                return false;
            }

            return true;
        }

        // * Overload * operator c = a*b
        // Atom operator*(const Atom& b) {
        //     if (this->var != b.var) {
        //         throw std::runtime_error("Atom Multiplication between different variables.");
        //     };
        //     Atom c;
        //     c.var = this->var;
        //     c.coeff = this->coeff * b.coeff;
        //     c.exp =  this->exp + b.exp;
        //     return c;
        // }

        Atom operator*(float b) {
            return Atom(this->coeff * b, this->var, this->exp);
        }

};

Atom operator/(float a, const Atom& b) {
    float coeff = a / b.coeff;
    float exp = - b.exp;
    
    return Atom(coeff, b.var, exp);
};

Atom operator*(float a, const Atom& b) {
    float coeff = a * b.coeff;
    return Atom(coeff, b.var, b.exp);
};