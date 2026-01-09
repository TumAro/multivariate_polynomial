#include <iostream>
#include <vector>
// #include "src/parser.h"
#include "src/polynomial.h"
#include "src/IOhandler.h"

// Polynomial leadDivision(Polynomial P1, Polynomial P2) {
//     for (Particle p : P1.polynom) {

//     }
// }


int main() {

    // Atom result = parseAtom("3.14*x^20.15");
    // std::cout << "Coeff: " << result.coeff << ", Var: " << result.var << ", Exp: " << result.exp << std::endl;

    // Particle p;
    // p.addAtom(Atom(1, 'y', 3));
    // p.addAtom(Atom(1, 'z', 2));
    // p.addAtom(Atom(1, 'x', 4));

    // std::vector<float> expVec = p.getExpVec();
    // for (auto& i : expVec ) std::cout << i << " "; std::cout << std::endl;

    std::vector<float> cubic = {1, 3, 3, 1};
    std::vector<float> quartic = {1, 0, 6, 4, 0};

    Polynomial A = ArrayToPoly(cubic, 'x', 3);
    Polynomial B = ArrayToPoly(quartic, 'y', 4);

    A.print();
    B.print();

    std::cout << "Addition===========" << std::endl;
    Polynomial X = A+B;
    X.print();

    std::cout << "Multiplication===========" << std::endl;
    Polynomial Y = A*B;
    Y.print();

    return 0;
}