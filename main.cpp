#include <iostream>
#include "src/atom.h"

int main() {
    Atom a(3, 'x', 2);
    Atom b(5, 'x', 1);
    Atom c(-2, 'x', 0);

    Atom poly[3] = {a, b, c};

    float sol = 0;
    for (int i = 0; i<3 ;i++) {
        sol = sol + poly[i].eval(2);
    };

    std::cout << sol<<std::endl;

    
    return 0;
}