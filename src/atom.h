#include <cmath>

class Atom {
    public:
        float coeff;
        int exp;
        char var;

        Atom(float a, char v, int e) : coeff(a), exp(e), var(v) {}

        float eval(float x) {
            return coeff * std::pow(x, exp);
        }
};