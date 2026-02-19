#include "linalg.h"

/*
Step 1: Find degree of the Polynom Matrix
Step 2: Generate n = (d+1) number of values of x
Step 3: Evaluate the Matrix at those X points
Step 4: Store the determinant of those matrices in Y
Step 5: Using these (xi, yi) interpolate to find an approximate polynomial.
*/

UniPolynom dceiDet(UniMatrix M) {
    int n = M.degree() + 1;
    // std::vector<float> X = genUniformArray(n, -(n)/2.0f, (n)/2.0f);
    std::vector<double> X = genSpacedInteger(n, -(n-1)/2);

    std::vector<double> Y(n);

    for (int i = 0; i < n; i++) {
        Y[i] = determinant(M(X[i]));
    }

    UniPolynom result = newtonInterpolation(X, Y);
    return result;
}


/*
Step 1: Find degree of the Polynom Matrix
Step 2: Generate n = ceil(n/2) many complex values of x
Step 3: Evaluate the Matrix at those X points
Step 4: Store the determinant and the conujgate of the determinant of those matrices in Y
Step 5: Using these (xi, yi) interpolate to find an approximate polynomial using the real part of the result.
*/

UniPolynom dceiComplexDet(UniMatrix M) {
    int n = M.degree() +1;
    int ceil = (n+1)/2;
    std::vector<std::complex<double>> complex = genSpacedComplex(ceil, std::complex<double>(0,1));

    std::vector<std::complex<double>> X, Y;

    for (const auto& z : complex) {

        std::complex<double> det = determinant(M(z));

        X.push_back(z);
        Y.push_back(det);
        X.push_back(std::conj(z));
        Y.push_back(std::conj(det));
    }

    UniPolynom result = newtonInterpolationComplex(X, Y);
    return result;
}
