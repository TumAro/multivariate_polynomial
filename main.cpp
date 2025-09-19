#include <iostream>
// #include "src/parser.h"
#include "src/polynomial.h"

// Polynomial leadDivision(Polynomial P1, Polynomial P2) {
//     for (Particle p : P1.polynom) {

//     }
// }


int main() {

    // Atom result = parseAtom("3.14*x^20.15");
    // std::cout << "Coeff: " << result.coeff << ", Var: " << result.var << ", Exp: " << result.exp << std::endl;

    Particle p;
    p.addAtom(Atom(1, 'y', 3));
    p.addAtom(Atom(1, 'z', 2));
    p.addAtom(Atom(1, 'x', 4));

    std::vector<float> expVec = p.getExpVec();
    for (auto& i : expVec ) std::cout << i << " "; std::cout << std::endl;

    return 0;
}