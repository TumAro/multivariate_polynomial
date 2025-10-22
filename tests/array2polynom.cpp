#include <iostream>
#include "../src/IOhandler.h"

int main() {

    std::vector<float> coeffs = {2, 0, 3, 69};
    Polynomial P = ArrayToPoly(coeffs, 'x'); 
    P.print();

    std::vector<float> test = PolyToArray(P, 'x');



    std::cout << "Array: ";
    for (float c : test) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    // Particle p;
    // p.addAtom(Atom(2,'x', 0));
    // p.print();
    return 0;
}