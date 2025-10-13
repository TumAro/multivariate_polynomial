#include <iostream>
#include "../src/atom.h"

int main() {
    Atom a1(3, 'x', 5);
    Atom b2(3, 'x', 5);

    // Atom inv = 1 / a;
    // Atom b = a / 3;

    // std::cout << inv.coeff << " " << inv.exp << std::endl;
    // std::cout << b.coeff << " " << b.exp << std::endl;

    // if ( a1 == b2 ) {
    //     std::cout << "yep" << std::endl;
    // } else {
    //     std::cout << "nope" << std::endl;
    // }

    std::cout << a1(2) << std::endl;


    return 0;
}