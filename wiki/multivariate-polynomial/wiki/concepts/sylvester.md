# concepts/sylvester

## what

Sylvester matrix: tool to find if two polynomials share a common root.
det(Sylvester) = resultant = 0 iff polynomials have common root (Sylvester criterion).

## construction

given F (deg n) and G (deg m), eliminate var x:

```
Sylvester(F,G) =  (m+n) × (m+n) matrix
  top m rows    : shifted copies of F coefficients
  bottom n rows : shifted copies of G coefficients
```

### univariate case (`NumericMatrix`)
```cpp
NumericMatrix sylvesterMat(UniPolynom F, UniPolynom G)
// src: Methods.cpp:80
// entries are doubles
// used when F,G already univariate
```

### multivariate case (`MultMatrix`)
```cpp
MultMatrix sylvesterMat(MultPolynom F, MultPolynom G, int var_idx=0)
// src: Methods.cpp:101
// entries are MultPolynom (remaining vars after eliminating var_idx)
// F.coeff(var_idx, k) extracts the k-th coeff polynomial in remaining vars
```

## Bezout's theorem connection

upper bound on #solutions of 2 curves = m × n (product of degrees).
Sylvester gives necessary+sufficient condition for intersection.

## what the resultant gives

`det(Sylvester(F,G))` is a polynomial in the remaining variables.
set = 0 → gives constraint on other variables at common roots.
iterate elimination → reduce to 1 variable → find roots numerically.

## code path

```
PolyGraph::eliminate(a, b, global_var)
    → sylvesterMat(MultPolynom, MultPolynom, var_index)   [Methods.cpp:101]
    → determinant / dceiDet / dceiComplexDet              [depends on cfg]
    → UniPolynom / MultPolynom (result)
```

## related

- [[dcei]] — determinant computation for the Sylvester matrix
- [[coeff-indexing]] — how MultPolynom.coeff() works
- [[data-flow]] — where Sylvester fits in the pipeline
