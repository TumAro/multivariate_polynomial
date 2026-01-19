#include <iostream>
#include <vector>
// #include "src/parser.h"
// #include "src/polynomial.h"
// #include "src/matrix.h"
// #include "src/IOhandler.h"
#include "src/module.hpp"

// Polynomial leadDivision(Polynomial P1, Polynomial P2) {
//     for (Particle p : P1.polynom) {

//     }
// }

void print(const std::string text) {
     std::cout << std::endl <<  text << std::endl;
}


int main() {

    // Atom result = parseAtom("3.14*x^20.15");
    // std::cout << "Coeff: " << result.coeff << ", Var: " << result.var << ", Exp: " << result.exp << std::endl;

    // Particle p;
    // p.addAtom(Atom(1, 'y', 3));
    // p.addAtom(Atom(1, 'z', 2));
    // p.addAtom(Atom(1, 'x', 4));

    // std::vector<float> expVec = p.getExpVec();
    // for (auto& i : expVec ) std::cout << i << " "; std::cout << std::endl;

    std::vector<float> cubic = {1, 3, 3, 1};
    std::vector<float> quartic = {1, 0, 6, 4, 0};

    Polynomial A = ArrayToPoly(cubic, 'x', 3);
    Polynomial B = ArrayToPoly(quartic, 'y', 4);

    A.print();
    B.print();

    print("Addition===========");
    Polynomial X = A+B;
    X.print();

    print("Multiplication===========");
    Polynomial Y = A*B;
    Y.print();

    // 
    // | 2x+3   5x^2    y       |
    // | 0      1       0       |
    // | 5      6       2y+x    |
    PolynomialMatrix N(3, 3);
    N[0][0] = ArrayToPoly({3, 2}, 'x', 1);
    N[0][1] = ArrayToPoly({0, 0, 5}, 'x', 2);
    N[0][2] = ArrayToPoly({0, 1}, 'y', 1);
    N[1][0] = ArrayToPoly({0}, '@', 0);
    N[1][1] = ArrayToPoly({1}, '@', 0);
    N[1][2] = ArrayToPoly({0}, '@', 0);
    N[2][0] = ArrayToPoly({5}, '@', 0);
    N[2][1] = ArrayToPoly({6}, '@', 0);
    N[2][2] = MultivariateArrayToPoly({0, 1, 2, 0}, {'x', 'y'}, {1, 1});

    // 3x3 matrix (robotics-style: joint angles, velocities, forces)
    // | cos(θ)≈1-x²    xy+1       -y+2    |
    // | 2xy-x         y²+x+3      xy      |  
    // | x²-y²         x-2y        1+xy    |


    PolynomialMatrix M(3, 3);
    // Row 0 (orientation terms)
    M[0][0] = MultivariateArrayToPoly({1, 0, -1,0,0,0,0,0,0}, {'x', 'y'}, {2, 2});                      // 1 - x²
    M[0][1] = MultivariateArrayToPoly({1, 0, 0, 1}, {'x', 'y'}, {1, 1});                   // 1 + xy
    M[0][2] = MultivariateArrayToPoly({2, 0, -1, 0}, {'x', 'y'}, {1, 1});                  // 2 - y

    // Row 1 (velocity coupling)
    M[1][0] = MultivariateArrayToPoly({0, -1, 0, 2}, {'x', 'y'}, {1, 1});                  // -x + 2xy
    M[1][1] = MultivariateArrayToPoly({3, 1, 0, 0, 1, 0}, {'x', 'y'}, {1, 2});                 // 3 + x + y²
    M[1][2] = MultivariateArrayToPoly({0, 0, 0, 1}, {'x', 'y'}, {1, 1});                   // xy

    // Row 2 (force/torque terms)
    M[2][0] = MultivariateArrayToPoly({0, 0, 1, 0, 0, 0, -1,0,0}, {'x', 'y'}, {2, 2});           // x² - y²
    M[2][1] = MultivariateArrayToPoly({0, 1, -2, 0}, {'x', 'y'}, {1, 1});                  // x - 2y
    M[2][2] = MultivariateArrayToPoly({1, 0, 0, 1}, {'x', 'y'}, {1, 1});                   // 1 + xy

    Polynomial D = determinant(M);

    print("Determinant================");
    M.print();
    D.print();

    PolynomialMatrix I{3,3};
    I[0][0] = ArrayToPoly({1}, '@', 0);
    I[0][1] = ArrayToPoly({0}, '@', 0);
    I[0][2] = ArrayToPoly({0}, '@', 0);
    I[1][0] = ArrayToPoly({0}, '@', 0);
    I[1][1] = ArrayToPoly({1}, '@', 0);
    I[1][2] = ArrayToPoly({0}, '@', 0);
    I[2][0] = ArrayToPoly({0}, '@', 0);
    I[2][1] = ArrayToPoly({0}, '@', 0);
    I[2][2] = ArrayToPoly({1}, '@', 0);


    print("Matrix mult================");
    PolynomialMatrix test1 = N*I;
    test1.print();

    print("------");
    PolynomialMatrix test2 = I^3;
    test2.print();

    print("------");
    PolynomialMatrix test3 = M*N;
    test3.print();

    return 0;
}