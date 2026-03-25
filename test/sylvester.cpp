#include "../src/polynomial.h"
#include "../src/linalg.h"

int main() {
    // Log("univariate sylvester Matrix");
    // UniPolynom F({0,0,1});
    // UniPolynom G({-10,1});
    // std::cout << "degree of F: " << F.degree() << std::endl;
    // std::cout << "degree of G: " << G.degree() << std::endl;
    // NumericMatrix SM = sylvesterMat(F, G);
    // float r = determinant(SM);
    // SM.print();
    // std::cout << "resultant: " << r << std::endl;

    // Log("multivariate sylvester: F=x+y, G=x-y");
    // MultPolynom MF1(2, 1), MG1(2, 1);
    // MF1.set({0, 1, 1, 0});   // x + y
    // MG1.set({0, 1, -1, 0});  // x - y
    // MultMatrix MSM1 = sylvesterMat(MF1, MG1);
    // MSM1.print();
    // UniPolynom res1 = dceiComplexDet(MSM1);
    // std::cout << "resultant (expect -2y): "; res1.print();

    // Log("second order polynom");
    // MultPolynom M(2, 1);
    // M.set({0,1,1,0}); // (x+y)
    // MultPolynom M_square = M*M;
    // MultPolynom M_cube = M*M*M;
    // std::cout << "M^2: "; M_square.print(); std::cout << std::endl;
    // std::cout << "M^3: "; M_cube.print();  std::cout  << std::endl;
    // MultMatrix sylv = sylvesterMat(M_square, M_cube);
    // sylv.print();

    // Log("4th order polynom");
    // MultPolynom X(2, 4); // P1: 3x⁴ - 7x³y + 2x²y² + 5xy³ - y⁴ + 4x³ - x²y + 6xy² - 3y³ + x² - 2xy + y² - 5x + 8y - 1
    // MultPolynom Y(2, 4); // P2: -2x⁴ + 5x³y - x²y² - 4xy³ + 6y⁴ - 3x³ + 7x²y - 2xy² + y³ - x² + 4xy - 6y² + 2x - y + 9
    // X.set({
    //         -1,  8,  1, -3, -1,   // (0,0)..(0,4)
    //         -5, -2,  6,  5,       // (1,0)..(1,3)
    //         1, -1,  2,           // (2,0)..(2,2)
    //         4, -7,               // (3,0)..(3,1)
    //         3                    // (4,0)
    // });
    // Y.set({
    //     9, -1, -6,  1,  6,   // (0,0)..(0,4)
    //     2,  4, -2, -4,       // (1,0)..(1,3)
    //     -1,  7, -1,           // (2,0)..(2,2)
    //     -3,  5,               // (3,0)..(3,1)
    //     -2                    // (4,0)
    // });
    // X.print(); std::cout << "\n";
    // Y.print(); std::cout << "\n";
    // MultMatrix fourth_sylv = sylvesterMat(X, Y);
    // fourth_sylv.print();

    Log("6th order polynom");
    MultPolynom M(2, 6);
    MultPolynom N(2, 6);
    M.set({
        1.39,  -4.75,  -2.25,  -2.77,   2.36,   1.77,   3.92,   // y^0
        -4.13,  -0.78,  -4.70,  -2.81,   0.05,  -4.73,          // y^1
        -3.01,   1.50,   0.45,  -2.80,   0.89,                  // y^2
        3.09,  -4.94,   3.06,   1.98,                           // y^3
        -1.60,  -3.45,   4.57,                                  // y^4
        -1.63,  -4.07,                                          // y^5
        -4.03                                                   // y^6
    });

    N.set({
        3.47,   1.04,   3.07,   2.30,   0.36,   4.73,  -1.21,  // y^0
        0.52,   3.29,   1.19,   3.62,   0.77,   2.05,          // y^1
        -4.54,  -2.72,  -2.11,  -4.20,  -2.67,                 // y^2
        -3.99,  -2.22,   1.36,  -1.35,                         // y^3
        -1.30,  -2.90,  -2.33,                                 // y^4
        4.37,   1.48,                                          // y^5
        1.09                                                   // y^6
    });
    M.print(); std::cout << "\n";
    N.print(); std::cout << "\n";
    MultMatrix sixth_sylv = sylvesterMat(M, N);
    UniPolynom resultant = dceiComplexDet(sixth_sylv);
    std::cout << "determinant: ";
    resultant.print();
    

}