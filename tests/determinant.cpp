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

    // Polynomial det1 = M1.det2x2();
    // std::cout << "Test 1 (real numbers): ";
    // det1.print();
    
    // Test 2: With polynomials
    // | x    2 |
    // | 3    x |
    // det = x*x - 2*3 = x^2 - 6
    
    PolynomialMatrix M2(2, 2);
    M2[0][0] = Polynomial() + Atom(1, 'x', 1);  // x
    M2[0][1] = Polynomial() + 2.0f;
    M2[1][0] = Polynomial() + 3.0f;
    M2[1][1] = Polynomial() + Atom(1, 'x', 1);  // x
    
    // Polynomial det2 = M2.det2x2();
    // std::cout << "Test 2 (polynomials): ";
    // det2.print();

    // Test 3: 3x3 real numbers
    // | 1  2  3 |
    // | 0  1  4 |
    // | 5  6  0 |
    // det = 1*(1*0 - 4*6) - 2*(0*0 - 4*5) + 3*(0*6 - 1*5)
    //     = 1*(-24) - 2*(-20) + 3*(-5)
    //     = -24 + 40 - 15 = 1

    PolynomialMatrix M3(3, 3);
    M3[0][0] = Polynomial() + 1.0f;
    M3[0][1] = Polynomial() + 2.0f;
    M3[0][2] = Polynomial() + 3.0f;
    M3[1][0] = Polynomial() + 0.0f;
    M3[1][1] = Polynomial() + 1.0f;
    M3[1][2] = Polynomial() + 4.0f;
    M3[2][0] = Polynomial() + 5.0f;
    M3[2][1] = Polynomial() + 6.0f;
    M3[2][2] = Polynomial() + 0.0f;

    std::cout << "\nTest 3 (3x3 real numbers, expected det: 1, trace: 2): " << std::endl;
    Polynomial det3 = determinant(M3);
    std::cout << "  det = "; det3.print();
    std::cout << "  trace = "; M3.trace().print();

    // Test 4: 3x3 with polynomials
    // | x  1  0 |
    // | 0  x  1 |
    // | 1  0  x |
    // det = x*(x^2 - 0) - 1*(0 - 1) + 0 = x^3 + 1

    PolynomialMatrix M4(3, 3);
    M4[0][0] = Polynomial() + Atom(1, 'x', 1);
    M4[0][1] = Polynomial() + 1.0f;
    M4[0][2] = Polynomial() + 0.0f;
    M4[1][0] = Polynomial() + 0.0f;
    M4[1][1] = Polynomial() + Atom(1, 'x', 1);
    M4[1][2] = Polynomial() + 1.0f;
    M4[2][0] = Polynomial() + 1.0f;
    M4[2][1] = Polynomial() + 0.0f;
    M4[2][2] = Polynomial() + Atom(1, 'x', 1);

    std::cout << "\nTest 4 (3x3 polynomials, expected det: x^3 + 1, trace: 3x): " << std::endl;
    Polynomial det4 = determinant(M4);
    std::cout << "  det = "; det4.print();
    std::cout << "  trace = "; M4.trace().print();


    // Test 5: 4x4 with mixed values including irrational numbers
    // | π    2    1    0   |
    // | 1   √2   -1    3   |
    // | 0    1    e    2   |
    // | -1   0    1   π/2  |

    PolynomialMatrix M5(4, 4);
    M5[0][0] = Polynomial() + 3.14159f;  // π
    M5[0][1] = Polynomial() + 2.0f;
    M5[0][2] = Polynomial() + 1.0f;
    M5[0][3] = Polynomial() + 0.0f;

    M5[1][0] = Polynomial() + 1.0f;
    M5[1][1] = Polynomial() + 1.41421f;  // √2
    M5[1][2] = Polynomial() + (-1.0f);
    M5[1][3] = Polynomial() + 3.0f;

    M5[2][0] = Polynomial() + 0.0f;
    M5[2][1] = Polynomial() + 1.0f;
    M5[2][2] = Polynomial() + 2.71828f;  // e
    M5[2][3] = Polynomial() + 2.0f;

    M5[3][0] = Polynomial() + (-1.0f);
    M5[3][1] = Polynomial() + 0.0f;
    M5[3][2] = Polynomial() + 1.0f;
    M5[3][3] = Polynomial() + 1.5708f;   // π/2

    std::cout << "\nTest 5 (4x4 with irrationals, expected trace: π + √2 + e + π/2 ≈ 8.85): " << std::endl;
    Polynomial det5 = determinant(M5);
    std::cout << "  det = "; det5.print();
    std::cout << "  trace = "; M5.trace().print();

    return 0;
}