#include <iostream>
#include "../src/particle.h"

int main() {

    Particle p1, p2;
    p1.atoms[0] = Atom(25,'x', 1);
    p2.atoms[0] = Atom(3,'x', 1);

    // p1.count = 1;
    // p2.count = 1;

    Particle p3 = p1 * p2;

    std::cout << p3.eval({{'x', 1}, {'y', 1}}) <<std::endl;


    return 0;

}