# structure

## repo layout

```
multivariate_polynomial/
├── src/                  ← active lib code
│   ├── polynomial.h      ← UniPolynom + MultPolynom class decls
│   ├── linalg.h          ← matrix class decls + free fn decls
│   ├── polygraph.h       ← PolyGraph + config decls
│   ├── utils.h           ← math helpers decls
│   ├── Univariate.cpp    ← UniPolynom impl
│   ├── Multivariate.cpp  ← MultPolynom impl
│   ├── LinAlgb.cpp       ← poly matrix impl
│   ├── Numerical.cpp     ← numeric matrix + LU det + Newton interp
│   ├── Methods.cpp       ← DCEI det + Sylvester matrix
│   └── PolyGraph.cpp     ← PolyGraph node impl
├── test/                 ← executables (not lib)
│   ├── test_case.cpp
│   ├── test_case_2.cpp
│   ├── mult.cpp
│   └── sylvester.cpp
├── documentation/
│   ├── MULTPOLYNOM_USAGE.md
│   └── TODO.md
├── main.cpp              ← scratch/debug entry (lexorderArray test)
├── CMakeLists.txt        ← build config
└── wiki/                 ← this wiki
```

## build system

- cmake 3.15+, C++17
- debug flags: `-fsanitize=address,undefined -O0 -g`
- lib target: `poly_lib` (static, from src/*.cpp)
- test targets: `test_case`, `test_mult`

## deps

| dep | use |
|-----|-----|
| GSL (gsl, gslcblas) | `gsl_poly_complex_solve` — finds roots of univariate poly |
| Boost.Variant2 | `boost::variant2::variant<MultPolynom, UniPolynom>` in PolyGraph nodes |

## header inclusion chain

```
utils.h
polynomial.h  → utils.h
linalg.h      → polynomial.h, utils.h
polygraph.h   → polynomial.h, linalg.h, utils.h
```
