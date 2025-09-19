#include <iostream>
#include "../src/particle.h"

int main() {

    Particle p1, p2;
    p1.addAtom(Atom(30, 'x', 2));
    p1.addAtom(Atom(1, 'y', 1));
    p1.addAtom(Atom(1, 'z', 1));

    p2.addAtom(Atom(5, 'x', 1));
    p2.addAtom(Atom(1, 'y', 1));



    Particle p3 = p1 / p2;

    std::cout << p3.eval({{'x', 1}, {'y', 1}, {'z', 1}}) <<std::endl;


    return 0;

}