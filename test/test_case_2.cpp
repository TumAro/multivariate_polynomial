#include "../src/polynomial.h"
#include "../src/linalg.h"
#include "texts/poly1.cpp"
#include "texts/poly2.cpp"

int main() {
    MultPolynom P1(2, 41);
    MultPolynom P2(2, 42);

    for (int i = 0; i < (int)poly1_powers.size(); i++)
        P1[poly1_powers[i]] = poly1_coeffs[i];

    for (int i = 0; i < (int)poly2_powers.size(); i++)
        P2[poly2_powers[i]] = poly2_coeffs[i];

    MultMatrix SM = sylvesterMat(P1, P2);
    UniPolynom R = dceiComplexDet(SM);

    std::cout << "resultant degree: " << R.degree() << std::endl;
    auto r = roots(R);

    double e = 1e-6;
    for (auto& root: r) {
        if (std::abs(root.imag()) < e)
            std::cout << "x = " << root.real() << "\n";
        else
            std::cout << "x = " << root.real() << " + " << root.imag() << "i\n";
    }

    auto shape = SM.shape();
    std::cout << "shape: " << shape[0] << "x" << shape[1] << std::endl;

}
