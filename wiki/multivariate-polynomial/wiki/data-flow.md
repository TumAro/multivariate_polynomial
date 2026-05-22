# data-flow

full pipeline: multivariate polynomials → common roots

## overview

```
MultPolynom F(vars, deg)   MultPolynom G(vars, deg)
        │                          │
        └──── PolyGraph::input ────┘
                     │
              NodeHandle a, b  (INPUT nodes, var_list=[x,y,...])
                     │
         PolyGraph::eliminate(a, b, global_var)
                     │
          builds Sylvester matrix (MultMatrix)
                     │
          computes det → resultant poly (fewer vars)
                     │
          [repeat eliminate for each variable until 1 var left]
                     │
         PolyGraph::solve(final_node)
                     │
          UniPolynom → GSL gsl_poly_complex_solve
                     │
          vector<complex<double>> roots
                     │
         [filter imag() < real_thresh if real_root=true]
                     │
         PolyGraph::getRoots(NodeHandle)
```

## step-by-step detail

### 1. input nodes
```cpp
NodeHandle a = g.input(F, {0, 1});  // F(x0, x1), vars=[0,1]
NodeHandle b = g.input(G, {0, 1});  // G(x0, x1), vars=[0,1]
```
stores poly + var_list in Node struct

### 2. elimination (variable elimination via resultant)
```cpp
NodeHandle c = g.eliminate(a, b, 0);  // eliminate var 0
```
- finds local var_index of global_var in node a's var_list
- validates: both nodes have MultPolynom, same var_list
- builds Sylvester matrix: `sylvesterMat(F, G, var_index)`
  - size: (m+n) × (m+n) where m=deg(G), n=deg(F)
  - entries are MultPolynom (remaining vars)
- computes determinant:
  - if 2 vars left (result will be univariate): use `final_method` (DCEI default)
  - else: cofactor expansion (symbolic)
- result poly has vars = input vars - 1
- new var_list = old var_list minus eliminated var

### 3. solve (root finding)
```cpp
NodeHandle s = g.solve(c);
```
- requires var_list.size() == 1
- converts poly to UniPolynom if needed
- calls `roots(UniPolynom)` → GSL solver
- if `real_root=true`: keeps only roots with |imag()| < real_thresh

### 4. retrieve roots
```cpp
auto r = g.getRoots(s);
```

## determinant methods (at elimination step)

| method | when used | how |
|--------|-----------|-----|
| cofactor | any non-final elimination | symbolic cofactor expansion on MultMatrix |
| DCEI | 2-var → 1-var (final), default | eval UniMatrix at n real pts [-1,1], Newton interp |
| DCEIC | 2-var → 1-var, complex variant | eval at n/2 unit-circle complex pts + conj, Newton interp |
| COFACTOR | override via config | symbolic cofactor on UniMatrix |

## data types through pipeline

```
MultPolynom (n vars)
    → MultMatrix (Sylvester, (n-1)-var entries)
        → UniMatrix (if 1-var entries)
            → NumericMatrix (evaluated at sample points)
                → double det values
                    → Newton interpolation
                        → UniPolynom (resultant)
                            → GSL roots
                                → complex<double>[]
```
