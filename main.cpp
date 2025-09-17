#include <iostream>
#include "src/parser.h"

int main() {

    Atom result = parseAtom("3.14*x^20.15");
    std::cout << "Coeff: " << result.coeff << ", Var: " << result.var << ", Exp: " << result.exp << std::endl;
    return 0;
}