#include "../src/polynomial.h"
#include "../src/linalg.h"
#include "texts/poly1.cpp"
#include "texts/poly2.cpp"
#include <iostream>
#include <complex>
#include <cmath>

int main() {
    MultPolynom P1(2, 41);
    MultPolynom P2(2, 42);
    for (int i = 0; i < (int)poly1_powers.size(); i++) P1[poly1_powers[i]] = poly1_coeffs[i];
    for (int i = 0; i < (int)poly2_powers.size(); i++) P2[poly2_powers[i]] = poly2_coeffs[i];

    MultMatrix SM = sylvesterMat(P1, P2);
    UniMatrix M(SM);

    int deg = M.degree();
    int n = deg + 1;
    int ceil = (n + 1) / 2;
    std::cout << "matrix degree estimate: " << deg << "  -> points ~ " << 2*ceil << "\n";
    std::cout << "matrix shape: " << M.rows << "x" << M.cols << "\n";

    // replicate dceiComplexDet point generation + det eval, instrument
    int nanEntries = 0, infEntries = 0, finiteEntries = 0;
    int nanDet = 0, infDet = 0, finiteDet = 0;
    double maxAbsDet = 0.0, maxAbsEntry = 0.0;

    for (int k = 1; k <= ceil; k++) {
        double theta = M_PI * k / (ceil + 1);
        std::complex<double> z = std::exp(std::complex<double>(0.0, theta));
        ComplexMatrix CM = M(z);

        // check entries
        for (int r = 0; r < CM.rows; r++)
            for (int c = 0; c < CM.cols; c++) {
                double a = std::abs(CM.matrix[r][c]);
                if (std::isnan(a)) nanEntries++;
                else if (std::isinf(a)) infEntries++;
                else { finiteEntries++; if (a > maxAbsEntry) maxAbsEntry = a; }
            }

        std::complex<double> det = determinant(CM);
        double ad = std::abs(det);
        if (std::isnan(ad)) nanDet++;
        else if (std::isinf(ad)) infDet++;
        else { finiteDet++; if (ad > maxAbsDet) maxAbsDet = ad; }

        if (k <= 3 || k == ceil)
            std::cout << "k=" << k << " |z|=" << std::abs(z)
                      << " |det|=" << ad << "\n";
    }

    std::cout << "\n--- ENTRIES (matrix cells eval'd on unit circle) ---\n";
    std::cout << "finite=" << finiteEntries << " inf=" << infEntries << " nan=" << nanEntries
              << "  maxAbsEntry=" << maxAbsEntry << "\n";
    std::cout << "--- DETERMINANTS ---\n";
    std::cout << "finite=" << finiteDet << " inf=" << infDet << " nan=" << nanDet
              << "  maxAbsDet=" << maxAbsDet << "\n";
    std::cout << "\ndouble max ~ 1.8e308\n";
    return 0;
}
