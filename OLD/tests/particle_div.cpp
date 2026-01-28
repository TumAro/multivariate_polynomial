#include <iostream>
#include "../src/particle.h"

int main() {
    // Testing: (30x^2yz) / (5xy) = 6xz
    // At x=1, y=1, z=1: 6*1*1 = 6

    Particle p1, p2;
    p1.addAtom(Atom(30, 'x', 2));
    p1.addAtom(Atom(1, 'y', 1));
    p1.addAtom(Atom(1, 'z', 1));

    p2.addAtom(Atom(5, 'x', 1));
    p2.addAtom(Atom(1, 'y', 1));

    Particle p3 = p1 / p2;

    // Use operator() instead of .eval()
    float result = p3({{'x', 1}, {'y', 1}, {'z', 1}});
    std::cout << result << std::endl;

    return 0;
}