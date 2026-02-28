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

## Display
[ ] - expPrint()  iterate all monomials using odometer pattern (no decode needed)
         start: exp = [0,0,...,0]
         tick:  increment exp[0]; if exp[0] > deg, reset to 0, carry into exp[1], etc.
[ ] - print()  show as monomials (e.g. "2x^2*y" not just raw coeffs)

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
[ ] - operator()(x1, x2, ..., xn)  plug in values for all variables

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
[ ] - univariate
[ ] - Multivariate
