#include "linalg.h"

NumericMatrix::NumericMatrix(int r, int c) : rows(r), cols(c) {
    matrix.resize(r, std::vector<double>(c));
}

ComplexMatrix::ComplexMatrix(int r, int c) : rows(r), cols(c) {
    matrix.resize(r, std::vector<std::complex<double>>(c));
}

// check if the matrix is square or not
void NumericMatrix::_check_square() const {
    if (rows != cols) {
        throw std::runtime_error(
            "Matrix must be square, given shape: (" +
            std::to_string(rows) + "x" + std::to_string(cols) + ").");
    }
}

void ComplexMatrix::_check_square() const {
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

ComplexMatrix ComplexMatrix::submatrix(int skip_r, int skip_c) const {
    ComplexMatrix sub(rows-1, cols-1);

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
double NumericMatrix::det2x2() const {
    _check_square();
    if (rows != 2) {
        throw std::runtime_error("Matrix is not of size 2!");
    }
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

std::complex<double> ComplexMatrix::det2x2() const {
    _check_square();
    if (rows != 2) {
        throw std::runtime_error("Matrix is not of size 2!");
    }
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

// separate determinant function
double determinant(const NumericMatrix& M) {
    if (M.rows == 1) {
        return M.matrix[0][0];
    }

    if (M.rows == 2) {
        return M.det2x2();
    }

    double result;
    for (int j = 0; j < M.cols; j++) {
        result = result + M.matrix[0][j] * cofactor(M, 0, j);
    }
    return result;
}

std::complex<double> determinant(const ComplexMatrix& M) {
    if (M.rows == 1) {
        return M.matrix[0][0];
    }

    if (M.rows == 2) {
        return M.det2x2();
    }

    std::complex<double> result;
    for (int j = 0; j < M.cols; j++) {
        result = result + M.matrix[0][j] * cofactor(M, 0, j);
    }
    return result;
}

// cofactor function
double cofactor(const NumericMatrix& M, int row, int col) {
    NumericMatrix sub = M.submatrix(row, col);
    int sign = ((row+col) % 2 == 0) ? 1 : -1;
    return sign * determinant(sub);
}

std::complex<double> cofactor(const ComplexMatrix& M, int row, int col) {
    ComplexMatrix sub = M.submatrix(row, col);
    double sign = ((row+col) % 2 == 0) ? 1 : -1;
    return sign * determinant(sub);
}


// Newton Interpolation Method
UniPolynom newtonInterpolation(const std::vector<double>& X, const std::vector<double>& Y) {
    if (X.size() != Y.size()) {
        throw std::runtime_error("The two set of points need of be of same size!");
    }

    int n = X.size();

    // divided difference table
    std::vector<std::vector<double>> divDiff(n, std::vector<double>(n, 0.0));

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

    // Build result polynomial from divided differences
    UniPolynom result(std::vector<float>{(float)divDiff[0][0]});
    UniPolynom basis(std::vector<float>{1.0f});

    for (int i = 1; i < n; i++) {
        std::vector<float> factor_coeffs = {(float)(-X[i-1]), 1.0f};
        basis = basis * UniPolynom(factor_coeffs);
        result = result + basis * (float)divDiff[0][i];
    }

    return result;
}

UniPolynom newtonInterpolationComplex(const std::vector<std::complex<double>>& X, std::vector<std::complex<double>>& Y) {
    if (X.size() != Y.size()) {
        throw std::runtime_error("The two set of points need of be of same size!");
    }

    int n = X.size();

    // divided difference table
    std::vector<std::vector<std::complex<double>>> divDiff(n, std::vector<std::complex<double>>(n, 0.0));

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

    // Build result polynomial from divided differences
    std::vector<std::complex<double>> result = {divDiff[0][0]};
    std::vector<std::complex<double>> basis = {1.0};

    for (int i = 1; i < n; i++) {
        // Multiply basis by (s - X[i-1])
        std::vector<std::complex<double>> new_basis(basis.size()+1);
        for (int j = 0; j < basis.size(); j++) {
            new_basis[j] += basis[j] * (-X[i-1]);
            new_basis[j+1] += basis[j];
        }
        basis = new_basis;

        // Add basis * divDiff[0][i] to result
        for (int j = 0; j < basis.size(); j++) {
            if (j >= result.size()) result.resize(j+1);
            result[j] += basis[j] * divDiff[0][i];
        }
    }

    // extracting only the real part
    std::vector<float> real_coeffs;
    for (auto& c : result) {
        real_coeffs.push_back((float)c.real());
    }

    return UniPolynom(real_coeffs);
}