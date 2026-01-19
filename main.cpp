#include "src/polynomial.h"

int main() {
    std::cout << "TEST: Basic unipoly + addition + degrees" << std::endl;
    UniPolynom P({1,1,1});
    P.print();

    UniPolynom A({1,2,3,4});
    UniPolynom B({1, 1, 0, 1, 0, 0});

    UniPolynom C = A + B;
    UniPolynom D = 23 + C;
    C.print();
    D.print();

    std::cout << A(1);
}