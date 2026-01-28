#include <iostream>
#include "../src/polynomial.h"

int main() {

    // x+1
    Polynomial P1, P2;
    Particle p1, p2;
    p1.addAtom(Atom(1,'x',1));
    p2.addAtom(Atom(1,'@',0));

    P1.addParticle(p1);
    P1.addParticle(p2);


    // 2x+3
    Particle p3, p4;
    p3.addAtom(Atom(2,'x',1));
    p4.addAtom(Atom(3,'@',0));

    P2.addParticle(p3);
    P2.addParticle(p4);

    // testing sum -> (x+1) + (2x+3) = 3x+4
    // Polynomial P = P1 + P2;

    // testing mult -> (x+1) * (2x+3) = 2x^2 + 5x + 3
    Polynomial P = P1 * P2;

    P.print();


    return 0;
}