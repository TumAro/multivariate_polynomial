#include <iostream>
#include "../src/polynomial.h"

int main() {
    // Particles can't be added directly - use Polynomial for addition
    // Testing: (15xy) + (2xy) = 17xy
    // At x=2, y=1: 17*2*1 = 34

    Particle p1, p2;
    p1.addAtom(Atom(15, 'x', 1));
    p1.addAtom(Atom(1, 'y', 1));

    p2.addAtom(Atom(2, 'x', 1));
    p2.addAtom(Atom(1, 'y', 1));

    // Add via Polynomial
    Polynomial P;
    P.addParticle(p1);
    P.addParticle(p2);

    // Evaluate using operator()
    float result = P({{'x', 2}, {'y', 1}});
    std::cout << result << std::endl;

    return 0;
}