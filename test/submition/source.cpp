#include "../../src/polynomial.h"
#include "../../src/linalg.h"
#include "coeffs.hpp"

int main() {
    MultPolynom eq1, eq2, eq3;
    load_eqs(eq1, eq2, eq3);

    MultMatrix SM1 = sylvesterMat(eq2, eq3, 0);
    MultPolynom h4  = determinant(SM1);

    MultMatrix SM2 = sylvesterMat(eq1, h4, 1);
    UniPolynom  h5  = dceiComplexDet(SM2);

    auto t1_roots = roots(h5);

    double eps = 1e-6;

    for (auto& t1 : t1_roots) {
        if (std::abs(t1.imag()) >= eps) continue;
        double t1_val = t1.real();

        auto t2_poly = UniPolynom(eq1.partialEval(0, t1_val));
        for (auto& t2 : roots(t2_poly)) {
            if (std::abs(t2.imag()) >= eps) continue;
            double t2_val = t2.real();

            auto t3_poly = UniPolynom(eq2.partialEval(1, t1_val).partialEval(1, t2_val));
            for (auto& t3 : roots(t3_poly)) {
                if (std::abs(t3.imag()) >= eps) continue;
                std::cout << "t1=" << t1_val << "  t2=" << t2_val << "  t3=" << t3.real() << "\n";
            }
        }
    }
}
