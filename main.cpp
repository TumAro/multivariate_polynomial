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

}