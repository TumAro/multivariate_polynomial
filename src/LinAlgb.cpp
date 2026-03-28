#include "linalg.h"

// shape
std::vector<int> UniMatrix::shape() const {
    return {this->rows, this->cols};
}

std::vector<int> MultMatrix::shape() const {
    return {this->rows, this->cols};
}

std::vector<int> NumericMatrix::shape() const {
    return {this->rows, this->cols};
}

std::vector<int> ComplexMatrix::shape() const {
    return {this->rows, this->cols};
}

//private func
void UniMatrix::_check_square() const {
    if (rows != cols) {
        throw std::runtime_error(
            "Matrix must be square, given shape: (" +
            std::to_string(rows) + "x" + std::to_string(cols) + ").");
    }
}

void MultMatrix::_check_square() const {
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

UniMatrix::UniMatrix(const MultMatrix& M) : rows(M.rows), cols(M.cols) {
    matrix.resize(rows, std::vector<UniPolynom>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = UniPolynom(M[i][j]); // throws if entry vars != 1
}

// OLD constructor - kept for backward compatibility
MultMatrix::MultMatrix(int r, int c) : rows(r), cols(c) {
    // TODO: MIGRATE to MultMatrix(r, c, vars, degree) for proper initialization
    // Currently uses default MultPolynom() constructor (1 var, degree 0)
    matrix.resize(r, std::vector<MultPolynom>(c));
}

// NEW constructor - initializes all cells with same structure (recommended)
MultMatrix::MultMatrix(int r, int c, int vars, int degree) : rows(r), cols(c) {
    matrix.resize(r, std::vector<MultPolynom>(c, MultPolynom(vars, degree)));
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

ComplexMatrix UniMatrix::operator()(std::complex<double> x) const {
    ComplexMatrix M(this->rows, this->cols);

    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++){
            M.matrix[r][c] = (*this)[r][c](x);
        }
    }

    return M;
}

NumericMatrix MultMatrix::operator()(std::vector<float> vals) const {
    NumericMatrix M(this->rows, this->cols);

    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++){
            M.matrix[r][c] = (*this)[r][c](vals);
        }
    }

    return M;
}

ComplexMatrix MultMatrix::operator()(std::vector<std::complex<double>> vals) const {
    ComplexMatrix M(this->rows, this->cols);

    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++){
            M.matrix[r][c] = (*this)[r][c](vals);
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

MultPolynom MultMatrix::trace() {
    _check_square();

    if (rows == 0) {
        throw std::runtime_error("Cannot compute trace of empty matrix");
    }

    MultPolynom P = matrix[0][0];  // Start with first element

    for(int i = 1; i < rows; i++) {  // Start from i=1
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

MultMatrix MultMatrix::submatrix(int skip_r, int skip_c) const {
    MultMatrix sub(rows-1, cols-1);

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

MultPolynom MultMatrix::det2x2() const {
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

void MultMatrix::print() {
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

void MultMatrix::buildDegreeMat() {
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

int MultMatrix::degree() {
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

MultPolynom determinant(const MultMatrix& M) {
    if (M.rows == 1) {
        return M[0][0];
    }

    if (M.rows == 2) {
        return M.det2x2();
    }

    if (M.cols == 0) {
        throw std::runtime_error("Cannot compute determinant of empty matrix");
    }

    MultPolynom result = M[0][0] * cofactor(M, 0, 0);  // First term

    for (int j = 1; j < M.cols; j++) {  // Start from j=1
        result = result + M[0][j] * cofactor(M, 0, j);
    }
    return result;
}

MultPolynom cofactor(const MultMatrix& M, int row, int col) {
    MultMatrix sub = M.submatrix(row, col);
    int sign = ((row+col) % 2 == 0) ? 1 : -1;
    return sign * determinant(sub);
}