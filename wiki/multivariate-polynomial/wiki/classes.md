# classes

## class map

```
UniPolynom          — 1-variable polynomial (float coeffs)
MultPolynom         — n-variable polynomial (float coeffs, lex order)
UniMatrix           — matrix of UniPolynom
MultMatrix          — matrix of MultPolynom
NumericMatrix       — matrix of double
ComplexMatrix       — matrix of complex<double>
PolyGraph           — DAG orchestrator: input → eliminate → solve
```

---

## UniPolynom

**file**: src/polynomial.h + src/Univariate.cpp
**storage**: `vector<float> coeffs` — index = power, e.g. coeffs[2] = coeff of x²

### constructors
```cpp
UniPolynom()                     // coeffs = {0}
UniPolynom(int n)                // n zero coefficients
UniPolynom(vector<float> c)      // direct
UniPolynom({1.0, 2.0, 3.0})     // initializer list
explicit UniPolynom(MultPolynom) // convert 1-var MultPolynom
```

### key methods
| method | what |
|--------|------|
| `degree()` | highest non-zero coeff index |
| `lead()` | leading coeff |
| `intercept()` | coeffs[0] |
| `operator[](n)` | get/set coeff at power n |
| `operator()(float x)` | eval via Horner's method |
| `operator()(complex<double>)` | complex eval via Horner |
| `getCoeffs()` | returns coeffs vector |
| `print()` | human-readable output |

### arithmetic
`+`, `-`, `*` with UniPolynom or float; unary `-`
free fns: `float OP UniPolynom`

---

## MultPolynom

**file**: src/polynomial.h + src/Multivariate.cpp
**storage**: `vector<float> coeffs` flat array, lex order
**size**: `binomial(deg+vars, vars)` — NOT `(deg+1)^vars` [see concepts/coeff-indexing]

### constructors
```cpp
MultPolynom()              // vars=1, deg=0, coeffs={0}
MultPolynom(int vars, int deg)
```

### key methods
| method | what |
|--------|------|
| `degree()` | returns deg |
| `numVars()` | returns vars |
| `operator[](vector<int> exp)` | get/set coeff by exponent vec |
| `operator()(vector<float>)` | eval at point |
| `operator()(vector<complex<double>>)` | complex eval |
| `coeff(vector<int> partial)` | fix leading vars, return sub-poly |
| `coeff(int var_idx, int exp)` | fix one var at exp, return sub-poly |
| `partialEval(int var_idx, double val)` | sub val for one var, return (vars-1) poly |
| `index2exp(int idx)` | flat index → exponent vector |
| `set(vector<double>)` | bulk-set coefficients |
| `print()` / `expPrint()` | debug output |

### arithmetic
`+`, `-`, `*` with MultPolynom or float; unary `-`
free fns: `float OP MultPolynom`

---

## UniMatrix / MultMatrix

**file**: src/linalg.h + src/LinAlgb.cpp

```
UniMatrix(int r, int c)                      — matrix of UniPolynom
UniMatrix(const MultMatrix& M)               — convert MultMatrix→UniMatrix (1 var)
MultMatrix(int r, int c)                     — OLD: cells are default MultPolynom
MultMatrix(int r, int c, int vars, int deg)  — NEW recommended: all cells same structure
```

| method | what |
|--------|------|
| `operator[](i)` | row access |
| `operator()(float/vec)` | eval → NumericMatrix |
| `operator()(complex/vec)` | eval → ComplexMatrix |
| `trace()` | diagonal sum poly |
| `submatrix(r,c)` | remove row r + col c |
| `det2x2()` | fast 2×2 det |
| `degree()` | max poly degree in matrix |
| `buildDegreeMat()` | fill degree_matrix |
| `print()` | debug |

**constraint**: all cells in MultMatrix MUST have same vars/deg (use new constructor)

---

## NumericMatrix / ComplexMatrix

**file**: src/linalg.h + src/Numerical.cpp
plain `double` / `complex<double>` matrices; no poly

| method | what |
|--------|------|
| `submatrix(r,c)` | minor matrix |
| `det2x2()` | fast 2×2 |
| `print()` | NumericMatrix only |

free fns: `determinant()`, `determinantLU()`, `cofactor()` for both types

---

## PolyGraph

**file**: src/polygraph.h + src/PolyGraph.cpp

orchestrates solve pipeline via DAG of nodes

### PolySystemConfig
```cpp
struct PolySystemConfig {
    DetMethod final_method = DetMethod::DCEI;  // COFACTOR|DCEI|DCEIC|LU
    bool real_root         = true;             // filter complex roots
    double real_thresh     = 1e-6;             // imag() < thresh → "real"
    bool realtime          = false;            // [TODO] lazy exec flag
};
```

### NodeType
`INPUT` | `ELIMINATE` | `SOLVE` | `BACKSOLVE`

### Node (private)
```
type           NodeType
inputs         vector<NodeHandle>
var_list       vector<int>   — global var IDs present in this node's poly
polynomial     variant<MultPolynom, UniPolynom>
roots          vector<complex<double>>
var_to_eliminate int
dirty          bool
```

### public API
| method | signature | what |
|--------|-----------|------|
| `input` | `(MultPolynom, vector<int> var_list) → NodeHandle` | add input poly |
| `eliminate` | `(NodeHandle a, b, int global_var) → NodeHandle` | Sylvester resultant, remove var |
| `solve` | `(NodeHandle) → NodeHandle` | find roots of 1-var poly |
| `backSolve` | `(NodeHandle poly_h, roots_h, int var) → NodeHandle` | [TODO] back-substitute |
| `run` | `() → void` | no-op (eager exec already done at node create) |
| `getRoots` | `(NodeHandle) → vector<complex<double>>` | retrieve roots |

### execution model
eager: all computation happens at `eliminate()` / `solve()` call time.
`run()` exists for API consistency; lazy exec is [TODO].
