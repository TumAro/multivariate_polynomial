# Univariate POLYNOM
[x] - Univariate Polynom
[x] - Addition
    [x] with polynom
    [X] with float
[x] - Evaluate (plug in a value for x)
[x] - Substraction
    [x] with polynom
    [x] with float
[x] - Multiplication
[x] - get leading term + constant term


[ ] - Division

[x] - Highest Degree
[x] - Init: Set highest degree
[ ] - Equivalence

# Multivariate POLYNOM
[x] - Constructor: coeffs[(deg+1)^vars], zero-initialized
[x] - operator[](exp) non-const  (encode exp -> index inline)
[x] - operator[](exp) const      (same logic, read-only)


[ ] - setDegree(int new_deg): re-encode all coefficients into new base-(new_deg+1) array

## Arithmetic
[x] - Addition
    [x] with polynom
    [x] with float
[x] - Subtraction
    [x] with polynom
    [x] with float
    [x] negation (unary -)
[ ] - Multiplication
    [x] with float
    [x] with polynom

## Evaluation
[x] - operator()(x1, x2, ..., xn)  plug in values for all variables

# Lin algebra:
[ ] - addition
[ ] - multiplication
[ ] - transpose
[ ] - identity
[ ] - adjoint
[ ] - dot
[ ] - cross
[ ] - eigen?

## Determinant
[x] - univariate
[x] - Multivariate
