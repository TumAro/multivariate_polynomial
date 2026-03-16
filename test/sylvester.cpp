#include "../src/polynomial.h"
#include "../src/linalg.h"

int main() {
    Log("univariate sylvester Matrix");
    UniPolynom F({0,0,1});
    UniPolynom G({-10,1});
    std::cout << "degree of F: " << F.degree() << std::endl;
    std::cout << "degree of G: " << G.degree() << std::endl;
    NumericMatrix SM = sylvesterMat(F, G);
    float r = determinant(SM);
    SM.print();
    std::cout << "resultant: " << r << std::endl;

    Log("multivariate sylvester: F=x+y, G=x-y");
    MultPolynom MF1(2, 1), MG1(2, 1);
    MF1.set({0, 1, 1, 0});   // x + y
    MG1.set({0, 1, -1, 0});  // x - y
    MultMatrix MSM1 = sylvesterMat(MF1, MG1);
    MSM1.print();
    UniPolynom res1 = dceiComplexDet(MSM1);
    std::cout << "resultant (expect -2y): "; res1.print();


    Log("multivariate sylvester: F=x-y, G=x^2-1");
    MultPolynom MF2(2, 1), MG2(2, 2);
    MF2.set({0, 1, -1, 0});              // x - y
    MG2.set({-1, 0, 1, 0, 0, 0, 0, 0, 0}); // x^2 - 1
    MultMatrix MSM2 = sylvesterMat(MF2, MG2);
    MSM2.print();
    UniPolynom res2 = dceiComplexDet(MSM2);
    std::cout << "resultant (expect y^2-1): "; res2.print();

    Log("second order polynom");
    MultPolynom M(2, 1);
    M.set({0,1,1,0}); // (x+y)
    MultPolynom M_square = M*M;
    MultPolynom M_cube = M*M*M;
    std::cout << "M^2: "; M_square.print(); std::cout << std::endl;
    std::cout << "M^3: "; M_cube.print();  std::cout  << std::endl;
    MultMatrix sylv = sylvesterMat(M_square, M_cube);
    sylv.print();

}