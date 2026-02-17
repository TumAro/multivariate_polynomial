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


// UniPolynom dceiComplexDet(UniMatrix M) {

// }
