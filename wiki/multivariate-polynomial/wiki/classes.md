# classes

## class map

```
UniPolynom     — 1-var poly (float coeffs, power-indexed)
MultPolynom    — n-var poly (float coeffs, graded-lex flat array)
UniMatrix      — r×c matrix of UniPolynom
MultMatrix     — r×c matrix of MultPolynom
NumericMatrix  — r×c matrix of double
ComplexMatrix  — r×c matrix of complex<double>
PolyGraph      — DAG orchestrator: input → eliminate → solve
```

---

## UniPolynom

**files**: src/polynomial.h, src/Univariate.cpp
**storage**: `vector<float> coeffs` — index = power (coeffs[2] = coeff of x²)
**precision**: float (not double) — potential precision loss for high-degree roots

### constructors
```cpp
UniPolynom()                      // coeffs={0}
UniPolynom(int n)                 // n zero-slots
UniPolynom(vector<float> c)       // direct
UniPolynom({1.0f, 0.0f, 3.0f})   // initializer list → 3x² + 1
explicit UniPolynom(MultPolynom)  // only if MultPolynom.numVars()==1, throws otherwise
```

### accessors
| method | returns | notes |
|--------|---------|-------|
| `degree()` | int | walks from back, finds last non-zero coeff |
| `lead()` | float | coeff at degree() |
| `intercept()` | float | coeffs[0] |
| `getCoeffs()` | `vector<float>` | copy of internal storage |
| `operator[](int n)` | `float&` | mutable — NO bounds check, crashes if n≥size |
| `operator[](int n) const` | float | safe — returns 0.0 if n≥size |

### evaluation
| call | impl | notes |
|------|------|-------|
| `P(float x)` | Horner's method | O(deg), numerically stable |
| `P(complex<double> x)` | Horner's method | returns complex<double> |

### arithmetic — IMPLEMENTED
| op | with | result |
|----|------|--------|
| `+` | UniPolynom | overlap-add coeffs, zero-extends shorter |
| `+` | float | adds to coeffs[0] |
| `-` | UniPolynom | via unary `-` + `+` |
| `-` | float | via `+ (-a)` |
| `-` (unary) | — | negates all coeffs up to degree() |
| `*` | float | scalar multiply up to degree() |
| `*` | UniPolynom | nested loop, O(m·n), result deg = m+n |
| free `f OP P` | float | commutative wrappers |

### arithmetic — NOT IMPLEMENTED (TODO.md)
- `/` division (polynomial long division)
- `==` equivalence operator
- `setDegree(n)` resize

### gotchas
- `operator[](n)` non-const: NO bounds check — will crash if n ≥ coeffs.size()
- `degree()` scans backwards every call — not cached
- coeffs stored as `float`, roots computed as `double` → cast happens in `roots()`

---

## MultPolynom

**files**: src/polynomial.h, src/Multivariate.cpp
**storage**: `vector<float> coeffs` flat, graded-lex order
**size**: `binomial(deg+vars, vars)` — stores only total-degree ≤ deg terms
**fixed at construction**: vars and deg cannot change after init [TODO: setDegree]

### constructors
```cpp
MultPolynom()                  // vars=1, deg=0, coeffs={0.0}
MultPolynom(int vars, int deg) // size = C(deg+vars, vars)
```

### accessors
| method | returns | notes |
|--------|---------|-------|
| `degree()` | int | stored deg field, NOT actual max nonzero degree |
| `numVars()` | int | stored vars field |
| `operator[](vector<int> exp)` | `float&` | mutable; throws if exp.size()≠vars or sum>deg or negative |
| `operator[](vector<int> exp) const` | float | safe; returns 0.0 for out-of-range |
| `index2exp(int idx)` | `vector<int>` | flat idx → exponent vec; O(vars·deg) |
| `set(vector<double>)` | void | bulk-set; truncates to min(input,storage) size |

### evaluation
| call | impl | notes |
|------|------|-------|
| `P(vector<float>)` | inline exp decode, Horner-style | skips zero coeffs; early-out |
| `P(vector<complex<double>>)` | same, complex | returns complex<double> |

### coefficient extraction
| method | what | result type |
|--------|------|-------------|
| `coeff(vector<int> partial)` | fix first `partial.size()` vars to given exps | MultPolynom (remaining vars) |
| `coeff(int var_idx, int exp)` | fix single var at exponent | MultPolynom (vars-1) |
| `partialEval(int var_idx, double val)` | substitute numeric value for one var | MultPolynom (vars-1, same deg) |

### arithmetic — IMPLEMENTED
| op | with | result | notes |
|----|------|--------|-------|
| `+` | MultPolynom | max(vars), max(deg) | re-encodes via index2exp loop |
| `+` | float | same dims | adds to coeffs[0] only |
| `-` (unary) | — | same dims | negates all |
| `-` | MultPolynom | via unary + `+` | — |
| `-` | float | via `+ (-a)` | — |
| `*` | float | same dims | scales all |
| `*` | MultPolynom | max(vars), deg₁+deg₂ | O(size₁·size₂) nested loop; uses vecAdd for exp |
| free `f OP P` | float | commutative wrappers | — |

### arithmetic — NOT IMPLEMENTED (TODO.md)
- `/` division
- `==` equivalence
- `setDegree(int new_deg)` — re-encode to new base; would allow degree growth

### debug output
| method | format |
|--------|--------|
| `print()` | `{c0 c1 c2 ...}` flat coeff dump |
| `expPrint()` | `[e0,e1,...]: coeff` one line per term |

### gotchas
- `degree()` returns stored deg, NOT the actual polynomial degree (may be lower if trailing coeffs zero)
- `coeff()` iterates ALL coefficients — O(size) per call; called in tight loop inside sylvesterMat
- `*` MultPolynom: degree of result = deg₁+deg₂, but vars = max not sum — caller must ensure correct vars
- precision: float storage, but partialEval takes double val → silent narrowing at return

---

## UniMatrix

**files**: src/linalg.h, src/LinAlgb.cpp
**storage**: `vector<vector<UniPolynom>>`
**also has**: `degree_matrix` (int grid, populated by `buildDegreeMat()`)

### constructors
```cpp
UniMatrix(int r, int c)          // all cells = default UniPolynom (coeffs={0})
UniMatrix(const MultMatrix& M)   // convert: calls UniPolynom(M[i][j]) per cell
                                  // THROWS if any cell has vars != 1
```

### methods
| method | returns | notes |
|--------|---------|-------|
| `operator[](i)` | `vector<UniPolynom>&` | row access |
| `operator()(float x)` | NumericMatrix | evaluates every cell |
| `operator()(complex<double>)` | ComplexMatrix | evaluates every cell |
| `trace()` | UniPolynom | sum of diagonal; calls `_check_square()` |
| `submatrix(r,c)` | UniMatrix | removes row r + col c |
| `det2x2()` | UniPolynom | only for 2×2; throws otherwise |
| `degree()` | int | min(sum of row-maxima, sum of col-maxima) — Hadamard-style bound |
| `buildDegreeMat()` | void | fills `degree_matrix` |
| `print()` | void | row-by-row |

### not implemented
- matrix addition / subtraction
- matrix multiplication
- transpose, identity, inverse, adjoint, dot, cross, eigenvalues

### free functions (linalg.h)
```cpp
UniPolynom determinant(UniMatrix)    // cofactor expansion, recursive, O(n!)
UniPolynom cofactor(UniMatrix, r, c) // (-1)^(r+c) * det(submatrix)
UniPolynom dceiDet(UniMatrix)        // interpolation-based, O(n²) numeric det × n pts
UniPolynom dceiComplexDet(UniMatrix) // complex unit-circle variant
```

---

## MultMatrix

**files**: src/linalg.h, src/LinAlgb.cpp
**storage**: `vector<vector<MultPolynom>>`

### constructors
```cpp
MultMatrix(int r, int c)                   // OLD: cells = MultPolynom() (1-var, deg-0)
                                            // TODO: migrate all uses to new constructor
MultMatrix(int r, int c, int vars, int deg) // NEW recommended: all cells = MultPolynom(vars,deg)
```

### methods — same interface as UniMatrix
| method | returns | notes |
|--------|---------|-------|
| `operator[](i)` | `vector<MultPolynom>&` | row access |
| `operator()(vector<float>)` | NumericMatrix | eval all cells |
| `operator()(vector<complex<double>>)` | ComplexMatrix | eval all cells |
| `trace()` | MultPolynom | starts from [0][0], adds diagonal |
| `submatrix(r,c)` | MultMatrix | uses OLD constructor internally — cells lose vars/deg info |
| `det2x2()` | MultPolynom | only 2×2 |
| `degree()` | int | same Hadamard bound as UniMatrix |
| `buildDegreeMat()` | void | fills degree_matrix |
| `print()` | void | row-by-row |

### not implemented
- matrix addition / subtraction / multiplication
- transpose, identity, inverse, adjoint

### free functions
```cpp
MultPolynom determinant(MultMatrix)    // cofactor expansion, O(n!)
MultPolynom cofactor(MultMatrix, r, c)
UniPolynom  dceiDet(MultMatrix)        // converts to UniMatrix first
UniPolynom  dceiComplexDet(MultMatrix) // converts to UniMatrix first
MultMatrix  sylvesterMat(MultPolynom F, MultPolynom G, int var_idx=0)
```

### gotcha: submatrix uses OLD constructor
`MultMatrix::submatrix` constructs result with `MultMatrix(r-1,c-1)` (OLD ctor).
cells in the submatrix get vars=1, deg=0 initially, then are assigned from source.
works because `MultPolynom::operator=` is default (copy), but the internal `d` field of
the submatrix is stale until `degree()` is called.

---

## NumericMatrix

**files**: src/linalg.h, src/Numerical.cpp
**storage**: `vector<vector<double>>`

### methods
| method | returns | notes |
|--------|---------|-------|
| `operator[](i)` | `vector<double>&` | row access |
| `submatrix(r,c)` | NumericMatrix | minor |
| `det2x2()` | double | 2×2 only |
| `shape()` | `vector<int>` | {rows,cols} |
| `print()` | void | formatted rows |

### free functions
```cpp
double determinant(NumericMatrix)    // delegates to determinantLU
double determinantLU(NumericMatrix)  // partial-pivot LU, O(n³)
double cofactor(NumericMatrix, r, c) // (-1)^(r+c) * det(submatrix)
NumericMatrix sylvesterMat(UniPolynom F, UniPolynom G)  // builds (m+n)×(m+n) numeric Sylvester
```

### not implemented
- matrix arithmetic, transpose, inverse, etc.

---

## ComplexMatrix

**files**: src/linalg.h, src/Numerical.cpp
**storage**: `vector<vector<complex<double>>>`

### methods
| method | returns | notes |
|--------|---------|-------|
| `submatrix(r,c)` | ComplexMatrix | minor |
| `det2x2()` | complex<double> | 2×2 only |
| `shape()` | `vector<int>` | {rows,cols} |

### free functions
```cpp
complex<double> determinant(ComplexMatrix)    // LU for n>2, det2x2 for n==2, direct for n==1
complex<double> determinantLU(ComplexMatrix)  // partial-pivot LU, complex arithmetic
complex<double> cofactor(ComplexMatrix, r, c)
```

### not implemented
- `print()` (NumericMatrix only has it)
- matrix arithmetic

---

## PolyGraph

**files**: src/polygraph.h, src/PolyGraph.cpp

### config
```cpp
struct PolySystemConfig {
    DetMethod final_method = DetMethod::DCEI;
    // COFACTOR: symbolic, exact, O(n!) — slow for large matrices
    // DCEI:     real interp, default — fast, slight numerical drift
    // DCEIC:    complex interp — more stable [?], same speed
    // LU:       declared in enum but NOT handled in eliminate() switch — falls through [BUG?]

    bool real_root    = true;    // filter: keep only roots with |imag()| < real_thresh
    double real_thresh = 1e-6;   // hardcoded default
    bool realtime     = false;   // declared but unused — lazy exec not implemented
};
```

### node types
| type | created by | holds |
|------|-----------|-------|
| INPUT | `input()` | MultPolynom + var_list |
| ELIMINATE | `eliminate()` | resultant poly (MultPolynom or UniPolynom) + new var_list |
| SOLVE | `solve()` | roots vector |
| BACKSOLVE | `backSolve()` | NOT IMPLEMENTED |

### public API
| method | signature | status |
|--------|-----------|--------|
| `input` | `(MultPolynom, vector<int>) → NodeHandle` | implemented |
| `eliminate` | `(NodeHandle, NodeHandle, int global_var) → NodeHandle` | implemented |
| `solve` | `(NodeHandle) → NodeHandle` | implemented |
| `backSolve` | `(NodeHandle, NodeHandle, int) → NodeHandle` | stub — NOT implemented |
| `run` | `() → void` | no-op; eager exec already done |
| `getRoots` | `(NodeHandle) → vector<complex<double>>` | implemented |

### eliminate() constraints (throws if violated)
- both nodes must hold MultPolynom (not UniPolynom)
- global_var must exist in node a's var_list
- both nodes must have identical var_lists

### solve() constraints
- node's var_list must have exactly 1 element

### execution model
eager: computation happens at `eliminate()` / `solve()` call time.
`run()` is a no-op placeholder for future lazy execution.
`dirty` flag exists in Node struct but is never set or read.

### not implemented
- backSolve (back-substitution to find values of eliminated variables)
- lazy/realtime execution
- LU det method in eliminate() switch (enum value exists, no case for it)

---

## utils (free functions)

**files**: src/utils.h, src/utils.cpp

| fn | what | impl note |
|----|------|-----------|
| `max(int,int)` / `min(int,int)` | int compare | shadows std:: versions |
| `pow(double, int)` | exponentiation by squaring | O(log n), handles negative exp |
| `factorial(int)` | iterative | returns -1 for n<0 |
| `binomial(int n, int k)` | C(n,k) | uses min(k,n-k) for efficiency |
| `joinVectors(v1,v2)` | concatenate float vectors | used in commented-out UniPolynom* code |
| `lexorderArray(total, vars)` | all exponent vecs with sum≤total | recursive; used in main.cpp scratch |
| `genUniformArray(n, a, b)` | n random floats in [a,b] | uses mt19937 |
| `genSpacedInteger(n, start)` | [start, start+1, ..., start+n-1] as double | |
| `genSpacedComplex(n, start)` | start + i·k for k=0..n-1 | steps along imaginary axis |
| `vecAdd(u,v)` | element-wise int vec add | zero-pads shorter vec |
| `Log(txt)` / `lineEnd()` | print helpers | thin wrappers over cout |
