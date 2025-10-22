#include <iostream>
#include "../src/module.hpp"


int main() {
    // Test 1: Real numbers only
    // | 2  3 |
    // | 1  4 |
    // det = 2*4 - 3*1 = 8 - 3 = 5
    
    PolynomialMatrix M1(2, 2);
    M1[0][0] = Polynomial() + 2.0f;
    M1[0][1] = Polynomial() + 3.0f;
    M1[1][0] = Polynomial() + 1.0f;
    M1[1][1] = Polynomial() + 4.0f;

    std::cout << "\nDebug Test 1:" << std::endl;
    Polynomial ad = M1[0][0] * M1[1][1];
    std::cout << "a*d (2*4): "; ad.print();

    Polynomial bc = M1[0][1] * M1[1][0];
    std::cout << "b*c (3*1): "; bc.print();

    Polynomial det = ad - bc;
    std::cout << "a*d - b*c: "; det.print();
    
    Polynomial det1 = M1.det2x2();
    std::cout << "Test 1 (real numbers): ";
    det1.print();
    
    // Test 2: With polynomials
    // | x    2 |
    // | 3    x |
    // det = x*x - 2*3 = x^2 - 6
    
    PolynomialMatrix M2(2, 2);
    M2[0][0] = Polynomial() + Atom(1, 'x', 1);  // x
    M2[0][1] = Polynomial() + 2.0f;
    M2[1][0] = Polynomial() + 3.0f;
    M2[1][1] = Polynomial() + Atom(1, 'x', 1);  // x
    
    Polynomial det2 = M2.det2x2();
    std::cout << "Test 2 (polynomials): ";
    det2.print();
    
    return 0;
}