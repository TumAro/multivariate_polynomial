#include "linalg.h"

//private func
void UniMatrix::_check_square() const {
    if (rows != cols) {
        throw std::runtime_error(
            "Matrix must be square, given shape: (" +
            std::to_string(rows) + "x" + std::to_string(cols) + ").");
    }
}

//Constructor
UniMatrix::UniMatrix(int r, int c) : rows(r), cols(c) {
    matrix.resize(r, std::vector<UniPolynom>(c));
}

// Accessories

// trace of matrix
UniPolynom UniMatrix::trace() {
    _check_square();
    UniPolynom P;
    
    for(int i = 0; i < rows; i++) {
        P = P + matrix[i][i];
    }
    return P;
}

// submatrix at ij of Matrix
UniMatrix UniMatrix::submatrix(int skip_r, int skip_c) const {
    UniMatrix sub(rows-1, cols-1);

    int sub_i = 0;
    for (int i = 0; i < rows; i++) {
        if (i == skip_r) continue;

        int sub_j = 0;
        for (int j = 0; j < cols; j++) {
            if (j == skip_c) continue;

            sub[sub_i][sub_j] = matrix[i][j];
            sub_j++;
        }
        sub_i++;
    }
    return sub;
}

UniPolynom UniMatrix::det2x2() const {
    _check_square();
    if (rows != 2) {
        throw std::runtime_error("Matrix is not of size 2!");
    }
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

// =================================================
// LINEAR ALGEBRA
// =================================================

UniPolynom determinant(const UniMatrix& M) {
    if (M.rows == 1) {
        return M[0][0];
    }

    if (M.rows == 2) {
        return M.det2x2();
    }

    UniPolynom result;
    for (int j = 0; j < M.cols; j++) {
        result = result + M[0][j] * cofactor(M, 0, j);
    }
    return result;
}

UniPolynom cofactor(const UniMatrix& M, int row, int col) {
    UniMatrix sub = M.submatrix(row, col);
    int sign = ((row+col) % 2 == 0) ? 1 : -1;
    return sign * determinant(sub);
}