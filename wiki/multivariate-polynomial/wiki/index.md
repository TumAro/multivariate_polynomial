# Multivariate Polynomial Library — Index

C++ lib: find common roots of 2+ multivariate polynomials.
Method: Sylvester resultant → variable elimination → univariate root find.
Use: real-time robot motion coord calc.

## pages

| page | what |
|------|------|
| [structure](structure.md) | repo layout, build, deps |
| [classes](classes.md) | all C++ classes: fields, methods, relations |
| [data-flow](data-flow.md) | full pipeline: inputs → roots |
| [api](api.md) | usage examples + quick ref |
| [concepts/sylvester](concepts/sylvester.md) | Sylvester matrix + resultant |
| [concepts/dcei](concepts/dcei.md) | DCEI determinant methods |
| [concepts/coeff-indexing](concepts/coeff-indexing.md) | MultPolynom lex order storage |

## quick facts

- 2 poly classes: `UniPolynom` (1-var), `MultPolynom` (n-var)
- 4 matrix classes: `UniMatrix`, `MultMatrix`, `NumericMatrix`, `ComplexMatrix`
- 1 graph class: `PolyGraph` — orchestrates full solve pipeline
- root finding: GSL `gsl_poly_complex_solve`
- det methods: LU (numeric), cofactor (poly), DCEI/DCEIC (poly via interpolation)
- deps: C++17, GSL, Boost.Variant2

## recent updates

- 2026-05-22: initial wiki population from codebase
