#include "../src/polynomial.h"
#include "../src/linalg.h"

int main() {
    Log("univariate sylvester Matrix");
    UniPolynom F({0,0,1});
    UniPolynom G({-10,1});
    std::cout << "degree of F: " << F.degree() << std::endl;
    std::cout << "degree of G: " << G.degree() << std::endl;
    NumericMatrix SM = sylvesterMat(F, G);
    float r = determinant(SM);
    SM.print();
    std::cout << "resultant: " << r;

}