#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include "polynomial.h"

class PolynomialMatrix {
    public:
    int rows, cols;

    std::vector<std::vector<Polynomial>> matrix;

    PolynomialMatrix(int r, int c) : rows(r), cols(c) {
        matrix.resize(r, std::vector<Polynomial>(c));
    }

    // * get and set methods with M[i][j]
    // for modifying
    std::vector<Polynomial>& operator[](int i) {
        return matrix[i];
    }

    // for reading
    const std::vector<Polynomial>& operator[](int i) const {
        return matrix[i];
    }

    // finding trace
    Polynomial trace(){
        _check_square();
        Polynomial P;

        for (int i = 0; i < rows; i++) {
            P = P + matrix[i][i];
        }
        return P;
    }

    // submatrix
    PolynomialMatrix submatrix(int skip_r, int skip_c) const {
        PolynomialMatrix sub(rows-1, cols-1);

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

    const Polynomial det2x2() const {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    // print the matrix
    void print() {
        for (int r = 0; r < rows ; r++) {
            std::cout << "| ";
            for (int c = 0; c < cols; c++) {
                matrix[r][c].print();
            }
            std::cout << "|" << std::endl;
        }
    }

    // Matrix * Matrix
    PolynomialMatrix operator*(const PolynomialMatrix& N) const {
        if (this->cols != N.rows) {
            std::cerr << "Error: Multiplication shape is not matching" << std::endl;
        }

        int same = this->cols;
        int rows = this->rows;
        int cols = N.cols;
        PolynomialMatrix M(rows, cols);

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                Polynomial val;
                for (int i = 0; i < same; i++) {
                    val = val + this->matrix[r][i] * N[i][c];
                }
                M[r][c] = val;
            }
        }

        return M;
    }

    // Matrix * Polynom
    PolynomialMatrix operator*(const Polynomial& a) const {
        PolynomialMatrix M(this->rows, this->cols);
        
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                M[i][j] = a * this->matrix[i][j];
            }
        }

        return M;
    }

    // Matrix ^ n
    PolynomialMatrix operator^(const int& n) const {
        PolynomialMatrix M = *this;
        for (int i = 0; i < n-1; i++) {
            M = M * (*this);
        }
        return M;
    }

    private:
    void _check_square() const {
        if (rows != cols) {
            throw std::runtime_error(
                "Matrix must be square, given shape: (" +
                std::to_string(rows) + "x" + std::to_string(cols) + ")."
            );
        }
    }
};

PolynomialMatrix operator*(const Polynomial& a, const PolynomialMatrix& M) {
    return M * a;
}

#endif