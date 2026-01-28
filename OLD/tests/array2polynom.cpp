#include <iostream>
#include <vector>
#include "../src/IOhandler.h"

void testMultivariate() {
    std::cout << "--- Testing Multivariate Array to Poly ---" << std::endl;

    // Case 1: 2D System (x, y)
    // Polynomial: 1 + 2y + 3x + 4xy
    // Dims: [2, 2] (degree 0 to 1 for both)
    // Flattened (Row Major): 
    // [0,0]->1, [0,1]->2, [1,0]->3, [1,1]->4
    std::vector<float> coeffs2D = {1, 2, 3, 4}; 
    std::vector<char> vars2D = {'x', 'y'};
    std::vector<int> dims2D = {2, 2};

    std::cout << "\nTest 1: 2D (x, y)" << std::endl;
    std::cout << "Expected: 1 + 2y + 3x + 4xy" << std::endl;
    std::cout << "Result:   ";
    Polynomial P2 = MultivariateArrayToPoly(coeffs2D, vars2D, dims2D);
    P2.print();


    // Case 2: 3D System (x, y, z)
    // Polynomial: 5z + 7xyz
    // Dims: [2, 2, 2] (Total size 8)
    // Indices:
    // z term -> x^0 y^0 z^1 -> Index [0,0,1] -> 0*4 + 0*2 + 1 = 1
    // xyz term -> x^1 y^1 z^1 -> Index [1,1,1] -> 1*4 + 1*2 + 1 = 7
    std::vector<float> coeffs3D(8, 0.0);
    coeffs3D[1] = 5; // z
    coeffs3D[7] = 7; // xyz

    std::vector<char> vars3D = {'x', 'y', 'z'};
    std::vector<int> dims3D = {2, 2, 2};

    std::cout << "\nTest 2: 3D (x, y, z)" << std::endl;
    std::cout << "Expected: 5z + 7xyz" << std::endl;
    std::cout << "Result:   ";
    Polynomial P3 = MultivariateArrayToPoly(coeffs3D, vars3D, dims3D);
    P3.print();
    // Case 3: Mixed Dimensions & Higher Degrees
    // Variables: a, b, c
    // Dims: [3, 2, 4] -> Max degrees: a->2, b->1, c->3
    // Total Array Size: 3 * 2 * 4 = 24
    
    // Target Term 1: 10 * b   -> a=0, b=1, c=0
    // Index = 0*(2*4) + 1*(4) + 0*(1) = 4
    
    // Target Term 2: 3 * a^2 b c^3 
    // Indices: a=2, b=1, c=3
    // Index = 2*(8) + 1*(4) + 3*(1) = 16 + 4 + 3 = 23
    
    std::vector<float> coeffsMix(24, 0.0);
    coeffsMix[4] = 10;
    coeffsMix[23] = 3;

    std::vector<char> varsMix = {'a', 'b', 'c'};
    std::vector<int> dimsMix = {3, 2, 4};

    std::cout << "\nTest 3: Complex Mixed Dims [3, 2, 4]" << std::endl;
    std::cout << "Expected: 10b + 3a^2bc^3" << std::endl;
    std::cout << "Result:   ";
    Polynomial P4 = MultivariateArrayToPoly(coeffsMix, varsMix, dimsMix);
    P4.print();
}

int main() {
    // Original Test (Univariate)
    std::cout << "--- Testing Univariate ---" << std::endl;
    std::vector<float> coeffs = {2, 0, 3, 69};
    Polynomial P = ArrayToPoly(coeffs, 'x'); 
    P.print();

    // New Tests
    testMultivariate();

    return 0;
}