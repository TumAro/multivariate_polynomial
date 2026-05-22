# api

quick-ref usage examples

## 1. define multivariate polynomials

```cpp
#include "polygraph.h"

// F(x,y) = x² + y² - 1  (unit circle)
MultPolynom F(2, 2);
F[{2,0}] = 1.0;   // x²
F[{0,2}] = 1.0;   // y²
F[{0,0}] = -1.0;  // -1

// G(x,y) = x + y - 1  (line)
MultPolynom G(2, 1);
G[{1,0}] = 1.0;   // x
G[{0,1}] = 1.0;   // y
G[{0,0}] = -1.0;  // -1
```

## 2. set up PolyGraph + solve

```cpp
PolySystemConfig cfg;
cfg.final_method = DetMethod::DCEI;  // default, good choice
cfg.real_root    = true;             // keep only real roots
cfg.real_thresh  = 1e-6;

PolyGraph g(cfg);

// register input polynomials (var_list = global var IDs)
NodeHandle a = g.input(F, {0, 1});  // F uses vars 0,1
NodeHandle b = g.input(G, {0, 1});  // G uses vars 0,1

// eliminate var 0 → resultant in var 1
NodeHandle elim = g.eliminate(a, b, 0);

// find roots of univariate resultant
NodeHandle sol = g.solve(elim);

// retrieve
auto roots = g.getRoots(sol);
```

## 3. evaluate poly at a point

```cpp
MultPolynom P(2, 2);
P[{1,1}] = 3.0;  // 3xy

float val = P({1.0f, 2.0f});              // real: 6.0
complex<double> c = P({{1.0,0.5},{2.0,0.0}});  // complex eval
```

## 4. univariate polynomial directly

```cpp
UniPolynom P({-6.0, 1.0, 1.0});  // x² + x - 6 = (x-2)(x+3)
auto r = roots(P);               // returns {2.0, -3.0}

P.print();    // 1x^2 + 1x - 6
P.degree();   // 2
P(2.0f);      // 0.0 (root check)
```

## 5. determinant methods compared

```cpp
// COFACTOR: symbolic, exact, O(n!) — only feasible for small matrices
PolySystemConfig cfg;
cfg.final_method = DetMethod::COFACTOR;

// DCEI: real sample pts + Newton interp — fast, may drift for high degree
cfg.final_method = DetMethod::DCEI;

// DCEIC: complex unit-circle pts + conj pairs — more numerically stable [?]
cfg.final_method = DetMethod::DCEIC;
```

## 6. coeff access patterns

```cpp
MultPolynom P(3, 2);

// set x₀¹ x₁⁰ x₂¹ coefficient
P[{1,0,1}] = 5.0;

// extract sub-polynomial: fix first var at exp=1, get poly in remaining vars
MultPolynom sub = P.coeff(0, 1);  // coefficients of x₀¹ terms as poly in x₁,x₂

// partial evaluation: plug x₀=2.5, return poly in x₁,x₂
MultPolynom reduced = P.partialEval(0, 2.5);
```

## 7. 3+ variable example (2 eliminations)

```cpp
// F(x,y,z), G(x,y,z), H(x,y,z) — 3 polys, 3 vars
NodeHandle nF = g.input(F, {0,1,2});
NodeHandle nG = g.input(G, {0,1,2});
NodeHandle nH = g.input(H, {0,1,2});

// elim z from F,G → poly in x,y
NodeHandle fg = g.eliminate(nF, nG, 2);

// elim z from F,H → poly in x,y
NodeHandle fh = g.eliminate(nF, nH, 2);

// elim y from fg,fh → poly in x
NodeHandle uni = g.eliminate(fg, fh, 1);

// solve for x
NodeHandle sol = g.solve(uni);
auto x_roots = g.getRoots(sol);
```
