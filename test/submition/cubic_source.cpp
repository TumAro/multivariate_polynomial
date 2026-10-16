#include "../../src/polynomial.h"
#include "../../src/linalg.h"
#include "cubic_coeffs.hpp"
#include <chrono>

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    MultPolynom eq1, eq2, eq3;
    load_eqs(eq1, eq2, eq3);

    // step 1: eliminate t3 (cofactor expansion, as in the paper)
    MultMatrix SM1 = sylvesterMat(eq2, eq3, 0);
    std::cout << "SM1: " << SM1.rows << "x" << SM1.cols << "\n";
    MultPolynom h4 = determinant(SM1);
    std::cout << "h4 degree: " << h4.degree() << ", vars: " << h4.numVars() << "\n";

    // step 2: eliminate t2 (DCEIC)
    MultMatrix SM2 = sylvesterMat(eq1, h4, 1);
    std::cout << "SM2: " << SM2.rows << "x" << SM2.cols << "\n";
    UniPolynom h5 = dceiComplexDet(SM2, 27);  // degree = Bezout bound: 3 * 9
    std::cout << "h5 degree: " << h5.degree() << "\n";
    h5.print();
    std::cout << "\n";

    // step 3: roots + back-substitution
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
                double t3_val = t3.real();
                // eq2 gives t3 candidates; eq3 residual flags spurious ones
                float r1 = eq1(std::vector<float>{(float)t1_val, (float)t2_val});
                float r2 = eq2(std::vector<float>{(float)t3_val, (float)t1_val, (float)t2_val});
                float r3 = eq3(std::vector<float>{(float)t3_val, (float)t1_val, (float)t2_val});
                std::cout << "t1=" << t1_val << "  t2=" << t2_val << "  t3=" << t3_val
                          << "  |r|=(" << std::abs(r1) << ", " << std::abs(r2) << ", " << std::abs(r3) << ")\n";
            }
        }
    }

    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
    std::cerr << elapsed.count() << " s\n";
}
