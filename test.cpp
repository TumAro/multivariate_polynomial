#include "src/polynomial.h"

int main() {
    Log("TEST: Basic unipoly + addition + degrees");
    UniPolynom P({1,1,1});
    P.print();

    UniPolynom A({1,2,3,4});
    UniPolynom B({1, 1, 0, 1, 0, 0});

    UniPolynom C = A + B;
    UniPolynom D = 23 + C;
    C.print();
    D.print();

    std::cout << A(1);
    Log("=========================================");

    Log("TEST: Substraction");
    UniPolynom E = A - B;
    UniPolynom F = 3 - B;
    E.print();
    F.print();

    Log("=========================================");

    Log("TEST: multiplication -> float + Polynom");
    UniPolynom G = 5 * A * 2;
    G.print();

    UniPolynom I({1,2,3});      // 1+2x+3x^2
    UniPolynom J({0,2,0,3});    // 2x + 3x^3
    UniPolynom K = I*J;         // 2x + 4x^2 + 9x^3 + 6x^4 + 9x^5
    K.print();

    Log("=========================================");

    Log("TEST: mult Polynom");
    MultPolynom L(2,2);
    L = {1, 2, 1};

    MultPolynom M(2,3);
    M = {1,3,3,1};

    MultPolynom N(3,2);
    N = {1,2,2,1,2,1};

    L.print();
    M.print();
    N.print();

    Log("------ exponents");
    M.expPrint();
    N.expPrint();
}