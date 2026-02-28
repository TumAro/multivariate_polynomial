#include "src/polynomial.h"

int main() {
    Log("TEST: Construction + set + print");
    // vars=2, deg=2 => 3^2=9 coeffs; index order: (0,0),(1,0),(2,0),(0,1),(1,1),(2,1),(0,2),(1,2),(2,2)
    MultPolynom A(2, 2);
    A.set({1, 2, 0, 3});  // 1 + 2x + 3y
    A.print();
    A.expPrint();
    lineEnd();

    MultPolynom B(2, 2);
    B[{0,0}] = 5;
    B[{1,0}] = -1;
    B[{0,1}] = 2;
    B[{1,1}] = 3;         // 5 - x + 2y + 3xy
    B.print();
    B.expPrint();
    lineEnd();

    Log("=========================================");

    Log("TEST: Addition");
    MultPolynom C = A + B;   // 6 + x + 5y + 3xy
    C.print();
    lineEnd();

    MultPolynom D = A + 10.0f;   // 11 + 2x + 3y
    D.print();
    lineEnd();

    MultPolynom E = 10.0f + A;   // same
    E.print();
    lineEnd();

    Log("=========================================");

    Log("TEST: Subtraction + unary negation");
    MultPolynom negA = -A;   // -1 - 2x - 3y
    negA.print();
    lineEnd();

    MultPolynom F = B - A;   // 4 - 3x - y + 3xy
    F.print();
    lineEnd();

    MultPolynom G = B - 5.0f;   // 0 - x + 2y + 3xy
    G.print();
    lineEnd();

    MultPolynom H = 5.0f - B;   // 0 + x - 2y - 3xy
    H.print();
    lineEnd();

    Log("=========================================");

    Log("TEST: Scalar multiplication");
    MultPolynom scaled = A * 3.0f;   // 3 + 6x + 9y
    scaled.print();
    lineEnd();

    MultPolynom scaled2 = 3.0f * A;   // same
    scaled2.print();
    lineEnd();

    Log("=========================================");

    Log("TEST: Poly*Poly - 2 vars");
    // (1 + x) * (1 + y) = 1 + x + y + xy
    MultPolynom P(2, 1);
    P.set({1, 1, 0, 0});   // 1 + x
    MultPolynom Q(2, 1);
    Q.set({1, 0, 1, 0});   // 1 + y

    MultPolynom R = P * Q;   // deg=2: 1 + x + y + xy
    R.print();
    R.expPrint();
    lineEnd();

    Log("TEST: Poly*Poly - 3 vars");
    // (1 + x) * (1 + z) = 1 + x + z + xz
    // vars=3,deg=1 => 2^3=8 coeffs; idx4=(0,0,1)=z
    MultPolynom S(3, 1);
    S.set({1, 1, 0, 0, 0, 0, 0, 0});   // 1 + x
    MultPolynom T(3, 1);
    T.set({1, 0, 0, 0, 1, 0, 0, 0});   // 1 + z

    MultPolynom U = S * T;   // deg=2: 1 + x + z + xz
    U.print();
    U.expPrint();
    lineEnd();

    Log("=========================================");

    Log("TEST: Mixed degree addition (deg2 + deg3)");
    MultPolynom V(2, 3);
    V[{0,2}] = 1;   // y^2
    V[{0,3}] = 7;   // 7y^3

    MultPolynom W = A + V;   // deg=3 result, carries A terms + V terms
    W.print();
    W.expPrint();
    lineEnd();

    Log("=========================================");

    Log("TEST: index2exp roundtrip");
    // For vars=2, deg=3: verify index->exponents for first 6 indices
    MultPolynom X(2, 3);
    for (int i = 0; i < 6; i++) {
        std::vector<int> exp = X.index2exp(i);
        std::cout << "idx " << i << " -> (" << exp[0] << "," << exp[1] << ")" << std::endl;
    }
    lineEnd();

    Log("=========================================");

    Log("TEST: square");
    MultPolynom foo(1,1);
    foo.set({1,1});
    MultPolynom bar = foo * foo;
    bar.print();
}
