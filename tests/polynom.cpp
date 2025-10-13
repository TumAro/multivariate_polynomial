#include <iostream>
#include "../src/polynomial.h"

int main() {

    Polynomial P; 
    P = (2*Atom(1,'x',2)*Atom(1, 'y', 1)) + (Atom(1,'x',1)*Atom(1,'z', 1));


    P.print();
    Polynomial Q = P.partialEval({{'x', 5}});
    Q.print();
    return 0;
}