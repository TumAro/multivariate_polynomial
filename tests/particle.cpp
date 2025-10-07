#include <iostream>
#include "../src/particle.h"

int main() {
    Particle p;
    p = p * Atom(1,'x', 2);
    p = p * Atom(5,'y', 5);
    p = p * 10;

    // std::cout << p.coefficient << std::endl;

    Particle z;
    z.addAtom(Atom(50, 'x', 2));
    z = z * Atom(1, 'y', 2);

    if (p == z) {
        std::cout << "yep" << std::endl;
    } else {
        std::cout << "nope" << std::endl;
    }

    return 0;
}