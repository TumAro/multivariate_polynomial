#include <cmath>


class Atom {
    public:
        float coeff;
        int exp;
        char var;

        Atom() : coeff(0), exp(0), var('x') {}
        Atom(float a, char v, int e) : coeff(a), exp(e), var(v) {}

        float eval(float x) {
            return coeff * std::pow(x, exp);
        }
};

