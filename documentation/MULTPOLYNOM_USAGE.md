# MultPolynom and MultMatrix Usage Guide

## MultPolynom - Multivariate Polynomial

### Constructors

```cpp
// Default constructor - creates 1-var, degree-0 polynomial (constant)
MultPolynom p;              // vars=1, deg=0, coeffs={0.0}

// Standard constructor - specify variables and degree
MultPolynom p(3, 5);        // 3 variables, degree 5
```

### Setting and Accessing Coefficients

```cpp
MultPolynom p(3, 2);        // 3 variables, degree 2

// Set coefficient using exponent vector
p[{1, 0, 2}] = 3.5;         // Sets coefficient for x₁¹ · x₂⁰ · x₃² to 3.5
p[{0, 1, 1}] = 2.0;         // Sets coefficient for x₁⁰ · x₂¹ · x₃¹ to 2.0

// Get coefficient (const access)
float coef = p[{1, 0, 2}];  // Returns 3.5
```

### Evaluation

**IMPORTANT: MultPolynom requires VECTOR input for evaluation**

```cpp
MultPolynom p(2, 3);        // 2 variables, degree 3
p[{1, 0}] = 3.0;            // Coefficient for x₁
p[{0, 1}] = 2.0;            // Coefficient for x₂

// Evaluate at point (x₁=2.0, x₂=1.0)
std::vector<float> vals = {2.0, 1.0};
float result = p(vals);     // Returns 3.0*2.0 + 2.0*1.0 = 8.0

// Complex evaluation
std::vector<std::complex<double>> c_vals = {{1.0, 0.5}, {2.0, 0.0}};
std::complex<double> c_result = p(c_vals);
```

### Algebraic Operations

```cpp
MultPolynom p1(2, 3);
MultPolynom p2(2, 3);

MultPolynom sum = p1 + p2;      // Addition
MultPolynom diff = p1 - p2;     // Subtraction
MultPolynom prod = p1 * p2;     // Multiplication
MultPolynom scaled = p1 * 3.5;  // Scalar multiplication
MultPolynom neg = -p1;          // Negation
```

### Printing

```cpp
p.print();      // Prints: (vars, deg) - {coeff₀ coeff₁ coeff₂ ...}
p.expPrint();   // Prints: [exp vector]: coefficient for each term
```

---

## MultMatrix - Matrix of Multivariate Polynomials

### Constructors

```cpp
// NEW RECOMMENDED: All polynomials have same structure (homogeneous)
MultMatrix M(2, 2, 3, 5);   // 2x2 matrix, all cells are (3-var, deg-5) polynomials

// OLD (backward compatibility): Uses default constructor for each cell
MultMatrix M_old(2, 2);     // 2x2 matrix, cells are (1-var, deg-0) polynomials
                            // TODO: Migrate to new constructor!
```

### Important Design Constraint

**ALL polynomials in a MultMatrix must have the SAME number of variables and degree**

This is enforced by using the new constructor `MultMatrix(rows, cols, vars, degree)`.

### Setting Coefficients

```cpp
MultMatrix M(2, 2, 3, 5);   // All cells: 3 vars, degree 5

// Set coefficient in specific cell
M[0][0][{1, 2, 1}] = 3.5;   // Cell [0][0], coefficient for x₁¹ · x₂² · x₃¹

// Assign entire polynomial (if needed with old constructor)
MultMatrix M_old(2, 2);
M_old[0][0] = MultPolynom(3, 5);    // Replace default with proper structure
M_old[0][0][{1, 2, 1}] = 3.5;       // Now can set coefficients
```

### Evaluation

**IMPORTANT: MultMatrix evaluation requires VECTOR input**

```cpp
MultMatrix M(2, 2, 3, 2);   // 2x2 matrix, 3 variables, degree 2

// Set some coefficients
M[0][0][{1, 0, 0}] = 3.0;
M[1][1][{0, 1, 0}] = 2.0;

// Evaluate at point (x₁=2.0, x₂=1.0, x₃=3.0)
std::vector<float> vals = {2.0, 1.0, 3.0};
NumericMatrix result = M(vals);     // Returns 2x2 numeric matrix

// Complex evaluation
std::vector<std::complex<double>> c_vals = {{1.0, 0.5}, {2.0, 0.0}, {3.0, 0.0}};
ComplexMatrix c_result = M(c_vals);
```

**API CHANGE**: Old API `M(5.0)` no longer works. Must use vector: `M({5.0})`

### Matrix Operations

```cpp
MultMatrix M(3, 3, 2, 2);

// Trace (sum of diagonal)
MultPolynom tr = M.trace();         // Returns a MultPolynom

// Determinant
MultPolynom det = determinant(M);   // Returns a MultPolynom

// Submatrix (remove row/col)
MultMatrix sub = M.submatrix(0, 0); // Remove row 0, col 0

// 2x2 determinant
MultPolynom det_2x2 = M.det2x2();   // Only for 2x2 matrices
```

---

## Quick Reference Examples

### Example 1: Simple 2-variable polynomial

```cpp
MultPolynom p(2, 3);            // p(x, y) with degree 3
p[{3, 0}] = 2.0;                // 2x³
p[{1, 1}] = 5.0;                // 5xy
p[{0, 2}] = 1.0;                // y²

// Evaluate at (x=1, y=2)
float val = p({1.0, 2.0});      // Returns 2(1)³ + 5(1)(2) + (2)² = 2 + 10 + 4 = 16
```

### Example 2: Matrix of polynomials

```cpp
// Create 2x2 matrix where each cell is a 2-variable, degree-2 polynomial
MultMatrix M(2, 2, 2, 2);

// Set M[0][0] = x + y
M[0][0][{1, 0}] = 1.0;          // x
M[0][0][{0, 1}] = 1.0;          // y

// Set M[1][1] = x² + 2y
M[1][1][{2, 0}] = 1.0;          // x²
M[1][1][{0, 1}] = 2.0;          // 2y

// Evaluate at (x=2, y=3)
NumericMatrix N = M({2.0, 3.0});
// N[0][0] = 2 + 3 = 5
// N[1][1] = 4 + 6 = 10
```

### Example 3: Computing determinant

```cpp
MultMatrix M(2, 2, 1, 2);       // 2x2 matrix, 1 variable (like UniPolynom), degree 2

// Set M = | x²   x  |
//         | 1    x  |
M[0][0][{2}] = 1.0;             // x²
M[0][1][{1}] = 1.0;             // x
M[1][0][{0}] = 1.0;             // 1
M[1][1][{1}] = 1.0;             // x

// Compute determinant: det = x² · x - x · 1 = x³ - x
MultPolynom det = determinant(M);
det.expPrint();                 // Shows x³ - x
```

---

## Migration Notes

### If using old constructor

```cpp
// OLD CODE (still works but not recommended)
MultMatrix M(2, 2);                         // Uses default (1-var, deg-0)
M[0][0] = MultPolynom(3, 5);               // Must assign before use

// NEW CODE (recommended)
MultMatrix M(2, 2, 3, 5);                  // All cells ready to use
M[0][0][{1, 2, 1}] = 3.5;                 // Can set coefficients immediately
```

### API Change for Evaluation

```cpp
// OLD API (no longer works)
NumericMatrix N = M(5.0);                  // ERROR: expects vector

// NEW API (must use)
NumericMatrix N = M({5.0});                // Vector with single element
NumericMatrix N = M({1.0, 2.0, 3.0});     // Vector with multiple values
```

---

## Internal Structure (Lexicographic Ordering)

MultPolynom stores coefficients in a **flat array** using lexicographic ordering:

For `MultPolynom p(2, 2)` (2 vars, degree 2):
- `coeffs[0]` → `[0,0]` → constant term
- `coeffs[1]` → `[1,0]` → x₁¹x₂⁰
- `coeffs[2]` → `[2,0]` → x₁²x₂⁰
- `coeffs[3]` → `[0,1]` → x₁⁰x₂¹
- `coeffs[4]` → `[1,1]` → x₁¹x₂¹
- `coeffs[5]` → `[2,1]` → x₁²x₂¹
- `coeffs[6]` → `[0,2]` → x₁⁰x₂²
- `coeffs[7]` → `[1,2]` → x₁¹x₂²
- `coeffs[8]` → `[2,2]` → x₁²x₂²

**Total size**: `(degree+1)^vars` = 3² = 9 coefficients

This is why vars and degree must be specified upfront and cannot be changed after construction.

---

## Summary

1. **Use new constructor**: `MultMatrix(rows, cols, vars, degree)` for cleaner code
2. **All cells same structure**: All polynomials in a matrix have same vars/degree
3. **Vector evaluation**: Always use vector input `M({x, y, z})` not `M(x)`
4. **Default constructor exists**: `MultPolynom()` creates minimal (1,0) placeholder
5. **Coefficients indexed by exponent vector**: `p[{1,2,3}]` for x₁¹x₂²x₃³

---

Last updated: 2026-03-05
