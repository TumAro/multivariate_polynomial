#include <iostream>
#include "../src/particle.h"

int main() {
    // Testing: (25x) * (3x) = 75x^2
    // At x=1, y=1: 75*1 = 75

    Particle p1, p2;
    p1.addAtom(Atom(25, 'x', 1));
    p2.addAtom(Atom(3, 'x', 1));

    Particle p3 = p1 * p2;

    // Use operator() instead of .eval()
    float result = p3({{'x', 1}, {'y', 1}});
    std::cout << result << std::endl;

    return 0;
}