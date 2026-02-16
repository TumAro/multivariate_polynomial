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
NumericMatrix UniMatrix::operator()(float x) const {
    NumericMatrix M(this->rows, this->cols);

    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++){
            M.matrix[r][c] = (*this)[r][c](x);
        }
    }

    return M;
}

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

// showing the matrix
void UniMatrix::print() {
    for (int r = 0; r < rows; r++) {
        std::cout << "| ";
        for (int c = 0; c < cols; c++) {
            matrix[r][c].print();
            std::cout << "  ";
        }
        std::cout << "|" <<std::endl;
    }
}

// building the degree matrix
void UniMatrix::buildDegreeMat() {
    this->degree_matrix.resize(this->rows, std::vector<int>(this->cols));

    for (int r=0; r < this->rows; r++) {
        for (int c=0; c < this->cols; c++) {
            this->degree_matrix[r][c] = this->matrix[r][c].degree();
        }
    }
}

// obtaining the degree of the polynom matrix
int UniMatrix::degree() {
    this->buildDegreeMat();
    this->d = -1;

    int dr = 0;
    int dc = 0;

    // checking and adding row wise maximums
    for (int r = 0; r < this->rows; r++) {
        int max = this->degree_matrix[r][0];

        for (int c = 1; c < this->cols; c++) {
            int deg = this->degree_matrix[r][c];
            if (deg > max) {
                max = deg;
            }
        }
        dr += max;
    }

    // checking and adding col wise maximums
    for (int c = 0; c < this->cols; c++) {
        int max = this->degree_matrix[0][c];

        for (int r = 1; r < this->rows; r++) {
            int deg = this->degree_matrix[r][c];
            if (deg > max) {
                max = deg;
            }
        }
        dc += max;
    }

    this->d = min(dr, dc);
    return this->d;
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