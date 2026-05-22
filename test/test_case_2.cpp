#include "../src/polynomial.h"
#include "../src/linalg.h"
#include "../src/polygraph.h"

int main() {
    MultPolynom P1(2, 41);
    MultPolynom P2(2, 42);

    std::vector<float> coeffs1 = genUniformArray(binomial(41+2, 2), -1, 1);
    std::vector<float> coeffs2 = genUniformArray(binomial(42+2, 2), -1, 1);

    P1.set(std::vector<double>(coeffs1.begin(), coeffs1.end()));
    P2.set(std::vector<double>(coeffs2.begin(), coeffs2.end()));

    MultMatrix SM = sylvesterMat(P1, P2);

    auto shape = SM.shape();
    std::cout << "shape: " << shape[0] << "x" << shape[1] << std::endl;
    std::cout << "degree: " << SM[0][0].degree() << std::endl;
    std::cout << "determinant of eval at 1.0:" << determinant(SM(std::vector({1.0f}))) << std::endl;;

}