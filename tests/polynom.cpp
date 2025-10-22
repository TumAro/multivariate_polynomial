#include <iostream>
#include "../src/module.hpp"

int main() {

    // Polynomial P; 
    // P = (2*Atom(1,'x',2)*Atom(1, 'y', 1)) + (Atom(1,'x',1)*Atom(1,'z', 1));


    // P.print();
    // Polynomial Q = P.partialEval({{'x', 5}});
    // Q.print();

    Polynomial p8 = Polynomial() + 8.0f;
std::cout << "p8[0] coefficient: " << p8.polynom[0].coefficient << std::endl;
std::cout << "p8[0] variables: ";
for (auto& v : p8.polynom[0].variables) {
    std::cout << v.first << "^" << v.second << " ";
}
std::cout << std::endl;

Polynomial neg3 = -(Polynomial() + 3.0f);
std::cout << "neg3[0] coefficient: " << neg3.polynom[0].coefficient << std::endl;
std::cout << "neg3[0] variables: ";
for (auto& v : neg3.polynom[0].variables) {
    std::cout << v.first << "^" << v.second << " ";
}
std::cout << std::endl;
    return 0;
}