#include "linalg.h"

Polynomial determinant(const PolynomialMatrix& M) {
    if (M.rows == 1) {
        return M[0][0];
    }

    if (M.rows == 2) {
        return M.det2x2();
    }

    Polynomial result;
    for (int j = 0; j < M.cols; j++) {
        result = result + M[0][j] * cofactor(M, 0, j);
    }
    return result;
}

Polynomial cofactor(const PolynomialMatrix& M, int row, int col) {
    PolynomialMatrix sub = M.submatrix(row, col);
    int sign = ((row + col) % 2 == 0) ? 1 : -1;
    return sign * determinant(sub);
}
