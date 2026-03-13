#include "../src/polynomial.h"
#include "../src/linalg.h"

int main() {
    Log("TEST: Construction + set + print");
    // vars=2, deg=2 => 3^2=9 coeffs; index order: (0,0),(1,0),(2,0),(0,1),(1,1),(2,1),(0,2),(1,2),(2,2)
    MultPolynom A(2, 2);
    A.set({1, 2, 0, 3});  // 1 + 2x + 3y
    A.print();
    A.expPrint();
    lineEnd();

    MultPolynom B(2, 2);
    B[{0,0}] = 5;
    B[{1,0}] = -1;
    B[{0,1}] = 2;
    B[{1,1}] = 3;         // 5 - x + 2y + 3xy
    B.print();
    B.expPrint();
    lineEnd();

    Log("=========================================");

    Log("TEST: Addition");
    MultPolynom C = A + B;   // 6 + x + 5y + 3xy
    C.print();
    lineEnd();

    MultPolynom D = A + 10.0f;   // 11 + 2x + 3y
    D.print();
    lineEnd();

    MultPolynom E = 10.0f + A;   // same
    E.print();
    lineEnd();

    Log("=========================================");

    Log("TEST: Subtraction + unary negation");
    MultPolynom negA = -A;   // -1 - 2x - 3y
    negA.print();
    lineEnd();

    MultPolynom F = B - A;   // 4 - 3x - y + 3xy
    F.print();
    lineEnd();

    MultPolynom G = B - 5.0f;   // 0 - x + 2y + 3xy
    G.print();
    lineEnd();

    MultPolynom H = 5.0f - B;   // 0 + x - 2y - 3xy
    H.print();
    lineEnd();

    Log("=========================================");

    Log("TEST: Scalar multiplication");
    MultPolynom scaled = A * 3.0f;   // 3 + 6x + 9y
    scaled.print();
    lineEnd();

    MultPolynom scaled2 = 3.0f * A;   // same
    scaled2.print();
    lineEnd();

    Log("=========================================");

    Log("TEST: Poly*Poly - 2 vars");
    // (1 + x) * (1 + y) = 1 + x + y + xy
    MultPolynom P(2, 1);
    P.set({1, 1, 0, 0});   // 1 + x
    MultPolynom Q(2, 1);
    Q.set({1, 0, 1, 0});   // 1 + y

    MultPolynom R = P * Q;   // deg=2: 1 + x + y + xy
    R.print();
    R.expPrint();
    lineEnd();

    Log("TEST: Poly*Poly - 3 vars");
    // (1 + x) * (1 + z) = 1 + x + z + xz
    // vars=3,deg=1 => 2^3=8 coeffs; idx4=(0,0,1)=z
    MultPolynom S(3, 1);
    S.set({1, 1, 0, 0, 0, 0, 0, 0});   // 1 + x
    MultPolynom T(3, 1);
    T.set({1, 0, 0, 0, 1, 0, 0, 0});   // 1 + z

    MultPolynom U = S * T;   // deg=2: 1 + x + z + xz
    U.print();
    U.expPrint();
    lineEnd();

    Log("=========================================");

    Log("TEST: Mixed degree addition (deg2 + deg3)");
    MultPolynom V(2, 3);
    V[{0,2}] = 1;   // y^2
    V[{0,3}] = 7;   // 7y^3

    MultPolynom W = A + V;   // deg=3 result, carries A terms + V terms
    W.print();
    W.expPrint();
    lineEnd();

    Log("=========================================");

    Log("TEST: index2exp roundtrip");
    // For vars=2, deg=3: verify index->exponents for first 6 indices
    MultPolynom X(2, 3);
    for (int i = 0; i < 6; i++) {
        std::vector<int> exp = X.index2exp(i);
        std::cout << "idx " << i << " -> (" << exp[0] << "," << exp[1] << ")" << std::endl;
    }
    lineEnd();

    Log("=========================================");

    Log("TEST: square");
    MultPolynom foo(1,1);
    foo.set({1,1});
    MultPolynom bar = foo * foo;
    bar.print();
    lineEnd();

    Log("=========================================");
    Log("NEW TESTS: Default Constructor");
    Log("=========================================");

    Log("TEST: Default constructor - creates (1,0) polynomial");
    MultPolynom defaultPoly;    // Should create 1-var, degree-0 (constant)
    defaultPoly.print();        // Should show (1,0) - {0.0}

    // Can assign a proper polynomial later
    defaultPoly = MultPolynom(2, 3);
    defaultPoly[{1, 2}] = 5.0;
    std::cout << "After assignment to (2,3) and setting [1,2]: ";
    defaultPoly.print();
    lineEnd();

    Log("=========================================");
    Log("NEW TESTS: MultPolynom Evaluation with Vectors");
    Log("=========================================");

    Log("TEST: Float vector evaluation");
    MultPolynom evalTest(2, 2);
    evalTest[{0, 0}] = 1.0;     // constant: 1
    evalTest[{1, 0}] = 3.0;     // 3x
    evalTest[{0, 1}] = 2.0;     // 2y
    evalTest[{1, 1}] = 5.0;     // 5xy
    std::cout << "Polynomial p(x,y) = 1 + 3x + 2y + 5xy" << std::endl;
    evalTest.print();

    std::vector<float> vals1 = {2.0, 1.0};  // x=2, y=1
    float result1 = evalTest(vals1);
    std::cout << "p(2, 1) = 1 + 3(2) + 2(1) + 5(2)(1) = 1 + 6 + 2 + 10 = " << result1 << std::endl;

    std::vector<float> vals2 = {0.0, 3.0};  // x=0, y=3
    float result2 = evalTest(vals2);
    std::cout << "p(0, 3) = 1 + 0 + 2(3) + 0 = " << result2 << std::endl;
    lineEnd();

    Log("TEST: Complex vector evaluation");
    MultPolynom complexTest(2, 1);
    complexTest[{0, 0}] = 1.0;   // 1
    complexTest[{1, 0}] = 2.0;   // 2x
    complexTest[{0, 1}] = 3.0;   // 3y
    std::cout << "Polynomial q(x,y) = 1 + 2x + 3y" << std::endl;

    std::vector<std::complex<double>> c_vals = {{1.0, 1.0}, {2.0, 0.0}};  // x=(1+i), y=2
    std::complex<double> c_result = complexTest(c_vals);
    std::cout << "q(1+i, 2) = 1 + 2(1+i) + 3(2) = 1 + 2 + 2i + 6 = (9, 2i)" << std::endl;
    std::cout << "Result: (" << c_result.real() << ", " << c_result.imag() << ")" << std::endl;
    lineEnd();

    Log("=========================================");
    Log("NEW TESTS: MultMatrix - New Constructor");
    Log("=========================================");

    Log("TEST: New MultMatrix constructor - all cells same structure");
    MultMatrix M(2, 2, 2, 2);   // 2x2 matrix, each cell is (2-var, deg-2)
    std::cout << "Created MultMatrix(2, 2, 2, 2)" << std::endl;
    std::cout << "Matrix dimensions: " << M.rows << "x" << M.cols << std::endl;

    // Set M[0][0] = x + y
    M[0][0][{1, 0}] = 1.0;      // x
    M[0][0][{0, 1}] = 1.0;      // y
    std::cout << "M[0][0] = x + y: ";
    M[0][0].print();

    // Set M[0][1] = x^2
    M[0][1][{2, 0}] = 1.0;      // x^2
    std::cout << "M[0][1] = x^2: ";
    M[0][1].print();

    // Set M[1][0] = 2y
    M[1][0][{0, 1}] = 2.0;      // 2y
    std::cout << "M[1][0] = 2y: ";
    M[1][0].print();

    // Set M[1][1] = xy + 1
    M[1][1][{0, 0}] = 1.0;      // constant
    M[1][1][{1, 1}] = 1.0;      // xy
    std::cout << "M[1][1] = xy + 1: ";
    M[1][1].print();
    lineEnd();

    Log("TEST: Old MultMatrix constructor (backward compatibility)");
    MultMatrix M_old(2, 2);     // TODO: Should migrate to M_old(2, 2, vars, deg)
    std::cout << "Created MultMatrix(2, 2) - uses default (1,0) polynomials" << std::endl;
    std::cout << "M_old[0][0] before assignment: ";
    M_old[0][0].print();        // Should show (1,0) - {0}

    // Must assign proper polynomial structure before use
    M_old[0][0] = MultPolynom(2, 2);
    M_old[0][0][{1, 1}] = 3.0;  // Now can set coefficients
    std::cout << "M_old[0][0] after assignment to (2,2) and setting [1,1]: ";
    M_old[0][0].print();
    lineEnd();

    Log("=========================================");
    Log("NEW TESTS: MultMatrix Evaluation");
    Log("=========================================");

    Log("TEST: MultMatrix vector evaluation (float)");
    MultMatrix M_eval(2, 2, 2, 1);  // 2x2, 2 vars, degree 1

    // M_eval = | 2x    x+y |
    //          | y      3  |
    M_eval[0][0][{1, 0}] = 2.0;     // 2x
    M_eval[0][1][{1, 0}] = 1.0;     // x
    M_eval[0][1][{0, 1}] = 1.0;     // y
    M_eval[1][0][{0, 1}] = 1.0;     // y
    M_eval[1][1][{0, 0}] = 3.0;     // 3

    std::cout << "Matrix M:" << std::endl;
    std::cout << "M[0][0] = 2x: "; M_eval[0][0].print();
    std::cout << "M[0][1] = x+y: "; M_eval[0][1].print();
    std::cout << "M[1][0] = y: "; M_eval[1][0].print();
    std::cout << "M[1][1] = 3: "; M_eval[1][1].print();

    std::vector<float> eval_vals = {2.0, 3.0};  // x=2, y=3
    std::cout << "\nEvaluating at (x=2, y=3):" << std::endl;
    NumericMatrix N = M_eval(eval_vals);
    std::cout << "Result[0][0] = 2(2) = " << N.matrix[0][0] << std::endl;
    std::cout << "Result[0][1] = 2+3 = " << N.matrix[0][1] << std::endl;
    std::cout << "Result[1][0] = 3 = " << N.matrix[1][0] << std::endl;
    std::cout << "Result[1][1] = 3 = " << N.matrix[1][1] << std::endl;
    lineEnd();

    Log("TEST: MultMatrix complex vector evaluation");
    MultMatrix M_complex(2, 2, 1, 1);  // Simple 1-var case for demo
    M_complex[0][0][{1}] = 1.0;        // x
    M_complex[1][1][{1}] = 2.0;        // 2x

    std::vector<std::complex<double>> c_eval_vals = {{1.0, 1.0}};  // x = 1+i
    ComplexMatrix CM = M_complex(c_eval_vals);
    std::cout << "M_complex evaluated at x=1+i:" << std::endl;
    std::cout << "Result[0][0] = (" << CM.matrix[0][0].real() << ", " << CM.matrix[0][0].imag() << ")" << std::endl;
    std::cout << "Result[1][1] = (" << CM.matrix[1][1].real() << ", " << CM.matrix[1][1].imag() << ")" << std::endl;
    lineEnd();

    Log("=========================================");
    Log("NEW TESTS: MultMatrix Operations");
    Log("=========================================");

    Log("TEST: trace() - sum of diagonal");
    MultMatrix M_trace(3, 3, 2, 1);  // 3x3, 2 vars, degree 1

    // Set diagonal to x, y, x+y
    M_trace[0][0][{1, 0}] = 1.0;    // x
    M_trace[1][1][{0, 1}] = 1.0;    // y
    M_trace[2][2][{1, 0}] = 1.0;    // x
    M_trace[2][2][{0, 1}] = 1.0;    // y (so [2][2] = x+y)

    std::cout << "3x3 Matrix with diagonal: [x, y, x+y]" << std::endl;
    MultPolynom tr = M_trace.trace();
    std::cout << "trace() = x + y + (x+y) = 2x + 2y: ";
    tr.print();
    tr.expPrint();
    lineEnd();

    Log("TEST: determinant() - 2x2");
    MultMatrix M_det(2, 2, 1, 2);   // 2x2, 1 var, degree 2

    // M_det = | x^2   x  |
    //         | 1     x  |
    M_det[0][0][{2}] = 1.0;         // x^2
    M_det[0][1][{1}] = 1.0;         // x
    M_det[1][0][{0}] = 1.0;         // 1
    M_det[1][1][{1}] = 1.0;         // x

    std::cout << "2x2 Matrix:" << std::endl;
    std::cout << "| x^2  x |" << std::endl;
    std::cout << "| 1    x |" << std::endl;

    MultPolynom det = determinant(M_det);
    std::cout << "det = x^2 * x - x * 1 = x^3 - x: ";
    det.print();
    det.expPrint();
    lineEnd();

    Log("TEST: determinant() - 3x3 (cofactor expansion)");
    MultMatrix M_det3(3, 3, 1, 1);  // 3x3, 1 var, degree 1

    // Simple 3x3 matrix with x
    M_det3[0][0][{1}] = 1.0;        // x
    M_det3[0][1][{0}] = 0.0;
    M_det3[0][2][{0}] = 0.0;
    M_det3[1][0][{0}] = 0.0;
    M_det3[1][1][{1}] = 1.0;        // x
    M_det3[1][2][{0}] = 0.0;
    M_det3[2][0][{0}] = 0.0;
    M_det3[2][1][{0}] = 0.0;
    M_det3[2][2][{1}] = 1.0;        // x

    std::cout << "3x3 Identity-like matrix with x on diagonal:" << std::endl;
    std::cout << "| x  0  0 |" << std::endl;
    std::cout << "| 0  x  0 |" << std::endl;
    std::cout << "| 0  0  x |" << std::endl;

    MultPolynom det3 = determinant(M_det3);
    std::cout << "det = x * x * x = x^3: ";
    det3.print();
    det3.expPrint();
    lineEnd();

    Log("=========================================");
    Log("ALL TESTS COMPLETED!");
    Log("=========================================");
}
