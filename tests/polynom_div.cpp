#include <iostream>
#include "../src/polynomial.h"

int main() {

    // x^2+1
    Polynomial P1, P2;
    Particle q1, q2;
    q1.addAtom(Atom(1,'x',2));
    q2.addAtom(Atom(1,'@',0));

    P1.addParticle(q1);
    P1.addParticle(q2);


    // 3x^3 + 2x + 1
    Particle p1, p2, p3;
    p1.addAtom(Atom(1, 'x', 3));  // x^3
    p2.addAtom(Atom(2, 'x', 1));  // 2x 
    p3.addAtom(Atom(1, '@', 0));  // 1

    P2.addParticle(p1);
    P2.addParticle(p2); 
    P2.addParticle(p3);

    // Polynomial P = P2 % P1;

    // P.print();

    // Polynomial P = P2 % P1;
    // P.print();

    // --------------------
    // Case 1: x²y + 3x
    Polynomial P3;
    Particle r1, r2;

    // First particle: x²y (coefficient 1, x², y¹)
    r1.addAtom(Atom(1, 'x', 2));  // x²
    r1.addAtom(Atom(1, 'y', 1));  // y

    // Second particle: 3x
    r2.addAtom(Atom(3, 'x', 1));  // 3x

    P3.addParticle(r1);
    P3.addParticle(r2);

    // Divisor: xy²
    Polynomial P4;
    Particle r3;
    r3.addAtom(Atom(1, 'x', 1));  // x
    r3.addAtom(Atom(1, 'y', 2));  // y²
    P4.addParticle(r3);

    // Case 2: x³y² + 2xy  
    Polynomial P5;
    Particle s1, s2;

    // First particle: x³y²
    s1.addAtom(Atom(1, 'x', 3));  // x³
    s1.addAtom(Atom(1, 'y', 2));  // y²

    // Second particle: 2xy
    s2.addAtom(Atom(2, 'x', 1));  // 2x
    s2.addAtom(Atom(1, 'y', 1));  // y

    P5.addParticle(s1);
    P5.addParticle(s2);

    // Divisor: x²y
    Polynomial P6;
    Particle s3;
    s3.addAtom(Atom(1, 'x', 2));  // x²
    s3.addAtom(Atom(1, 'y', 1));  // y
    P6.addParticle(s3);

    // Polynomial A = P3 / P4;     // (x²y + 3x) / (xy²)
    // Polynomial B = P5 / P6;     // (x³y² + 2xy) / (x²y)

    // A.print();
    // B.print();

    // 3x^2yz + 3y^2zx + 3xyz^2
    Polynomial T1;
    Particle a1, a2, a3;
    a1.addAtom(Atom(3, 'x', 2));
    a1.addAtom(Atom(1, 'y', 1));
    a1.addAtom(Atom(1, 'z', 1));

    a2.addAtom(Atom(1, 'x', 1));
    a2.addAtom(Atom(3, 'y', 2));
    a2.addAtom(Atom(1, 'z', 1));

    a3.addAtom(Atom(1, 'x', 1));
    a3.addAtom(Atom(1, 'y', 1));
    a3.addAtom(Atom(3, 'z', 2));

    T1.addParticle(a2);
    T1.addParticle(a3);
    T1.addParticle(a1);

    T1.print();

    Polynomial T2;
    Particle b1;
    b1.addAtom(Atom(1, 'x', 1));  // x
    b1.addAtom(Atom(1, 'y', 1));  // y²
    T2.addParticle(b1);

    T2.print();

    Polynomial P = T1 / T2;
    P.print();

    return 0;
}