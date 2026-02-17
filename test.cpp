#include "src/polynomial.h"
#include "src/linalg.h"

int main() {
    Log("TEST: Basic unipoly + addition + degrees");
    UniPolynom XY({1,1,1});
    XY.print();
    lineEnd();

    UniPolynom A({1,2,3,4});
    UniPolynom B({1, 1, 0, 1, 0, 0});

    UniPolynom C = A + B;
    UniPolynom D = 23 + C;
    C.print();
    lineEnd();
    D.print();
    lineEnd();

    std::cout << A(1);
    Log("=========================================");

    Log("TEST: Substraction");
    UniPolynom E = A - B;
    UniPolynom F = 3 - B;
    E.print();
    lineEnd();
    F.print();
    lineEnd();

    Log("=========================================");

    Log("TEST: multiplication -> float + Polynom");
    UniPolynom G = 5 * A * 2;
    G.print();
    lineEnd();

    UniPolynom I({1,2,3});      // 1+2x+3x^2
    UniPolynom J({0,2,0,3});    // 2x + 3x^3
    UniPolynom K = I*J;         // 2x + 4x^2 + 9x^3 + 6x^4 + 9x^5
    K.print();
    lineEnd();

    Log("=========================================");

    Log("TEST: mult Polynom");
    MultPolynom L(2,2);
    L = {1, 2, 1};

    MultPolynom M(2,3);
    M = {1,3,3,1};

    MultPolynom N(3,2);
    N = {1,2,2,1,2,1};

    L.print();
    lineEnd();
    M.print();
    lineEnd();
    N.print();
    lineEnd();

    Log("------ exponents");
    M.expPrint();
    N.expPrint();

    Log("=========================================");

    Log("TEST: uni Matrix - Identity");
    UniMatrix Mat1(3,3);
    Mat1[0][0] = std::vector<float>{1};
    Mat1[1][1] = std::vector<float>{1};
    Mat1[2][2] = std::vector<float>{1};
    Mat1.print();
    UniPolynom O = determinant(Mat1);
    O.print();
    lineEnd();
    std::cout << "DCEI:  ";
    UniPolynom dcei1 = dceiDet(Mat1);
    dcei1.print();
    lineEnd();

    Log("TEST: uni Matrix - Polynomial entries");
    UniMatrix Mat2(3,3);
    Mat2[0][0] = std::vector<float>{1, 2};        // 1 + 2x
    Mat2[0][1] = std::vector<float>{3};           // 3
    Mat2[0][2] = std::vector<float>{0, 1};        // x
    Mat2[1][0] = std::vector<float>{2, -1};       // 2 - x
    Mat2[1][1] = std::vector<float>{1, 0, 1};     // 1 + x^2
    Mat2[1][2] = std::vector<float>{4};           // 4
    Mat2[2][0] = std::vector<float>{1};           // 1
    Mat2[2][1] = std::vector<float>{-2, 3};       // -2 + 3x
    Mat2[2][2] = std::vector<float>{5, 1};        // 5 + x
    Mat2.print();
    UniPolynom P = determinant(Mat2);
    std::cout << "Determinant: ";
    P.print();
    lineEnd();
    std::cout << "DCEI:  ";
    UniPolynom dcei2 = dceiDet(Mat2);
    dcei2.print();
    lineEnd();

    Log("TEST: uni Matrix - 2x2");
    UniMatrix Mat3(2,2);
    Mat3[0][0] = std::vector<float>{1, 1};        // 1 + x
    Mat3[0][1] = std::vector<float>{2};           // 2
    Mat3[1][0] = std::vector<float>{3};           // 3
    Mat3[1][1] = std::vector<float>{4, -1};       // 4 - x
    Mat3.print();
    UniPolynom Q = determinant(Mat3);
    std::cout << "Determinant [-2 + 3x - x^2]: ";
    Q.print();
    lineEnd();
    std::cout << "DCEI:  ";
    UniPolynom dcei3 = dceiDet(Mat3);
    dcei3.print();
    lineEnd();

    Log("TEST: uni Matrix - 4x4 Higher degree polynomials");
    UniMatrix Mat4(4,4);
    Mat4[0][0] = std::vector<float>{2, 1, 0, 1};           // 2 + x + x^3
    Mat4[0][1] = std::vector<float>{-1, 2, 1};             // -1 + 2x + x^2
    Mat4[0][2] = std::vector<float>{3, 0, -2};             // 3 - 2x^2
    Mat4[0][3] = std::vector<float>{1, 1, 1, 1};           // 1 + x + x^2 + x^3
    Mat4[1][0] = std::vector<float>{4, -3, 2};             // 4 - 3x + 2x^2
    Mat4[1][1] = std::vector<float>{1, 0, 0, -1};          // 1 - x^3
    Mat4[1][2] = std::vector<float>{0, 5, 1};              // 5x + x^2
    Mat4[1][3] = std::vector<float>{2, 2};                 // 2 + 2x
    Mat4[2][0] = std::vector<float>{-2, 1, 3};             // -2 + x + 3x^2
    Mat4[2][1] = std::vector<float>{6};                    // 6
    Mat4[2][2] = std::vector<float>{1, -1, 1, -1};         // 1 - x + x^2 - x^3
    Mat4[2][3] = std::vector<float>{0, 0, 4};              // 4x^2
    Mat4[3][0] = std::vector<float>{3, 1};                 // 3 + x
    Mat4[3][1] = std::vector<float>{-4, 0, 2, 1};          // -4 + 2x^2 + x^3
    Mat4[3][2] = std::vector<float>{1, 3, -1};             // 1 + 3x - x^2
    Mat4[3][3] = std::vector<float>{5, -2, 0, 2};          // 5 - 2x + 2x^3
    Mat4.print();
    UniPolynom R = determinant(Mat4);
    std::cout << "Determinant (high degree): ";
    R.print();
    lineEnd();
    std::cout << "DCEI:  ";
    UniPolynom dcei4 = dceiDet(Mat4);
    dcei4.print();
    lineEnd();

    Log("TEST: uni Matrix - 3x3 Characteristic polynomial style");
    UniMatrix Mat5(3,3);
    Mat5[0][0] = std::vector<float>{3, -1};        // 3 - λ (represented as 3 - x)
    Mat5[0][1] = std::vector<float>{1};            // 1
    Mat5[0][2] = std::vector<float>{2};            // 2
    Mat5[1][0] = std::vector<float>{0};            // 0
    Mat5[1][1] = std::vector<float>{2, -1};        // 2 - λ
    Mat5[1][2] = std::vector<float>{-1};           // -1
    Mat5[2][0] = std::vector<float>{0};            // 0
    Mat5[2][1] = std::vector<float>{1};            // 1
    Mat5[2][2] = std::vector<float>{1, -1};        // 1 - λ
    Mat5.print();
    UniPolynom S = determinant(Mat5);
    std::cout << "Characteristic polynomial: ";
    S.print();
    lineEnd();
    std::cout << "DCEI:  ";
    UniPolynom dcei5 = dceiDet(Mat5);
    dcei5.print();
    lineEnd();

    Log("=========================================");

    Log("TEST: Degree Matrix Building");
    UniMatrix Mat6(3, 3);
    Mat6[0][0] = std::vector<float>{1, 2, 3};      // 1 + 2x + 3x^2 (degree 2)
    Mat6[0][1] = std::vector<float>{5};            // 5 (degree 0)
    Mat6[0][2] = std::vector<float>{0, 0, 1, 2};   // x^2 + 2x^3 (degree 3)
    Mat6[1][0] = std::vector<float>{3, 1};         // 3 + x (degree 1)
    Mat6[1][1] = std::vector<float>{0, 0, 0, 4};   // 4x^3 (degree 3)
    Mat6[1][2] = std::vector<float>{2, 1, 1};      // 2 + x + x^2 (degree 2)
    Mat6[2][0] = std::vector<float>{1};            // 1 (degree 0)
    Mat6[2][1] = std::vector<float>{0, 3, 2};      // 3x + 2x^2 (degree 2)
    Mat6[2][2] = std::vector<float>{4, 0, 0, 1};   // 4 + x^3 (degree 3)

    Mat6.buildDegreeMat();
    std::cout << "Matrix with polynomial entries:" << std::endl;
    Mat6.print();
    std::cout << "Degree of matrix (min of row/col max sums): " << Mat6.degree() << std::endl;
    std::cout << "Expected degree: min(3+3+3, 2+3+3) = min(9, 8) = 8" << std::endl;
    lineEnd();

    Log("=========================================");

    Log("TEST: Newton Interpolation - Simple case");
    std::vector<double> X1 = {0, 1, 2};
    std::vector<double> Y1 = {1, 3, 7};  // Points on y = 1 + x + x^2
    UniPolynom interp1 = newtonInterpolation(X1, Y1);
    std::cout << "Interpolating through (0,1), (1,3), (2,7)" << std::endl;
    std::cout << "Expected: 1 + x + x^2" << std::endl;
    std::cout << "Result: ";
    interp1.print();
    lineEnd();

    Log("TEST: Newton Interpolation - Linear case");
    std::vector<double> X2 = {0, 1};
    std::vector<double> Y2 = {2, 5};  // Points on y = 2 + 3x
    UniPolynom interp2 = newtonInterpolation(X2, Y2);
    std::cout << "Interpolating through (0,2), (1,5)" << std::endl;
    std::cout << "Expected: 2 + 3x" << std::endl;
    std::cout << "Result: ";
    interp2.print();
    lineEnd();

    Log("TEST: Newton Interpolation - Four points");
    std::vector<double> X3 = {-1, 0, 1, 2};
    std::vector<double> Y3 = {-1, 1, 3, 13};  // Points on y = 1 + x + 2x^2 + x^3
    UniPolynom interp3 = newtonInterpolation(X3, Y3);
    std::cout << "Interpolating through (-1,-1), (0,1), (1,3), (2,13)" << std::endl;
    std::cout << "Result: ";
    interp3.print();
    lineEnd();

}