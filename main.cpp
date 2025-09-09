#include <iostream>
#include "src/atom.h"

int main() {
    Atom a(3, 'x', 2);
    Atom b(5, 'x', 1);
    Atom c(-2, 'x', 0);

    Atom poly[3] = {a, b, c};

    // float sol = 0;
    // for (int i = 0; i<3 ;i++) {
    //     sol = sol + poly[i].eval(2);
    // };

    // std::cout << sol<<std::endl;

    Particle p1, p2;
    p1.atoms[0] = Atom(25,'x', 1);
    p2.atoms[0] = Atom(3,'x', 1);

    p1.count = 1;
    p2.count = 1;

    Particle p3 = p1 * p2;

    std::cout << p3.eval({{'x', 1}, {'y', 1}}) <<std::endl;
    return 0;
}