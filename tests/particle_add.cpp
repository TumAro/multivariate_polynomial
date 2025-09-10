#include <iostream>
#include "../src/particle.h"

int main() {
    Particle p1, p2;
    p1.addAtom(Atom(15, 'x', 1));
    p1.addAtom(Atom(1, 'y', 1));

    p2.addAtom(Atom(2, 'x', 1));
    p2.addAtom(Atom(1, 'y', 1));

    Particle p3 = p1 + p2;

    std::cout << p3.eval({{'x', 2}, {'y', 1}}) <<std::endl;

    return 0;
}