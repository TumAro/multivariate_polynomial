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

}