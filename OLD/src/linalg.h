#pragma once

#include "matrix.h"

// Function declarations
Polynomial determinant(const PolynomialMatrix& M);
Polynomial cofactor(const PolynomialMatrix& M, int row, int col);
