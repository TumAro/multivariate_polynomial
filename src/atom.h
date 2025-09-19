#include <cmath>

class Atom {
    public:
        float coeff;
        float exp;
        char var;

        Atom() : coeff(0), exp(0), var('x') {}
        Atom(float a, char v, float e) : coeff(a), exp(e), var(v) {}

        float eval(float x) {
            return coeff * std::pow(x, exp);
        }

        // * Overload / operator, A = a / b
        Atom operator/(const Atom& b) {
            float coeff = this->coeff / b.coeff;
            float exp = this->exp - b.exp;

            if (this->var == b.var) {
                return Atom(coeff, this->var, exp);
            }
            return Atom();
        }
};

