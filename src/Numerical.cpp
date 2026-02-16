#include "linalg.h"

NumericMatrix::NumericMatrix(int r, int c) : rows(r), cols(c) {
    matrix.resize(r, std::vector<float>(c));
}

// check if the matrix is square or not
void NumericMatrix::_check_square() const {
    if (rows != cols) {
        throw std::runtime_error(
            "Matrix must be square, given shape: (" +
            std::to_string(rows) + "x" + std::to_string(cols) + ").");
    }
}

// submatrix at ij of Matrix
NumericMatrix NumericMatrix::submatrix(int skip_r, int skip_c) const {
    NumericMatrix sub(rows-1, cols-1);

    int sub_i = 0;
    for (int i = 0; i < rows; i++) {
        if (i == skip_r) continue;

        int sub_j = 0;
        for (int j = 0; j < cols; j++) {
            if (j == skip_c) continue;

            sub.matrix[sub_i][sub_j] = matrix[i][j];
            sub_j++;
        }
        sub_i++;
    }
    return sub;
}

// determinant for 2x2 matrix
float NumericMatrix::det2x2() const {
    _check_square();
    if (rows != 2) {
        throw std::runtime_error("Matrix is not of size 2!");
    }
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

// separate determinant function
float determinant(const NumericMatrix& M) {
    if (M.rows == 1) {
        return M.matrix[0][0];
    }

    if (M.rows == 2) {
        return M.det2x2();
    }

    float result;
    for (int j = 0; j < M.cols; j++) {
        result = result + M.matrix[0][j] * cofactor(M, 0, j);
    }
    return result;
}

// cofactor function
float cofactor(const NumericMatrix& M, int row, int col) {
    NumericMatrix sub = M.submatrix(row, col);
    int sign = ((row+col) % 2 == 0) ? 1 : -1;
    return sign * determinant(sub);
}


// Newton Interpolation Method
UniPolynom newtonInterpolation(std::vector<float> X, std::vector<float> Y) {
    if (X.size() != Y.size()) {
        throw std::runtime_error("The two set of points need of be of same size!");
    }

    int n = X.size();

    // divided difference table
    std::vector<std::vector<float>> divDiff(n, std::vector<float>(n, 0.0f));

    //initialising the first column with Y values
    for (int r = 0; r < n; r++) {
        divDiff[r][0] = Y[r];
    }

    // computing divided differences
    for (int c = 1; c < n; c++) {
        for (int r = 0; r < n - c; r++) {
            divDiff[r][c] = (divDiff[r+1][c-1] - divDiff[r][c-1]) / (X[r+c] - X[r]);
        }
    }

    // The first row of the table is the coefficients of the polynom
    std::vector<float> coeffs = {divDiff[0][0]};
    UniPolynom result(coeffs);
    UniPolynom basis(std::vector<float>{1.0f});

    for (int i = 1; i < n; i++) {
        basis = basis * UniPolynom({-X[i-1], 1.0f});
        result = result + basis*divDiff[0][i];
    }

    return result;
}