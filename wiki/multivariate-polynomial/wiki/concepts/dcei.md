# concepts/dcei

## what

DCEI = Determinant via Characteristic Equation Interpolation.
Alternative to symbolic cofactor expansion for polynomial matrices.
trades exactness for speed: evaluate matrix numerically at sample points, interpolate result.

## why

cofactor expansion on polynomial matrices: O(n!) complexity, exponential coeff growth.
DCEI: evaluate n times at scalar x, get n (x, det) pairs, Newton-interpolate → polynomial.

## DCEI (real variant)

**fn**: `dceiDet(UniMatrix M)` — src: Methods.cpp:14
**also**: `dceiDet(MultMatrix M)` → converts to UniMatrix first

```
1. d = M.degree()  (max poly degree in matrix)
2. n = d + 1       (need n+1 points to reconstruct deg-d poly, using n)
3. X = n evenly-spaced points in [-1, 1]
4. Y[i] = det( M(X[i]) )    [numeric det via LU]
5. result = newtonInterpolation(X, Y)
```

**sample pts**: `X[i] = -1 + 2i/(n-1)` — bounded range prevents det blowup.

## DCEIC (complex variant)

**fn**: `dceiComplexDet(UniMatrix M)` — src: Methods.cpp:41

```
1. d = M.degree(), ceil = (d+1)/2 (uses conjugate symmetry → half pts needed)
2. X = ceil pts on unit circle: e^(i·π·k/(ceil+1)) for k=1..ceil
3. for each z: compute det(M(z)), add (z, det) and (conj(z), conj(det)) to X,Y
4. result = newtonInterpolationComplex(X, Y)  [extracts real part of coeffs]
```

**why unit circle**: |z|=1 bounds det magnitude → stable interpolation.
**why complex conj**: real polynomial → conj(P(z)) = P(conj(z)), halves computation.

## Newton interpolation

`newtonInterpolation(X, Y)` — src: Numerical.cpp:199
builds divided difference table → reconstructs polynomial.

`newtonInterpolationComplex(X, Y)` — src: Numerical.cpp:234
same idea but complex X,Y → takes real part of result coefficients.

## when each det method is used (in PolyGraph::eliminate)

| condition | method |
|-----------|--------|
| var_list.size() > 2 | `determinant(MultMatrix)` — symbolic cofactor |
| var_list.size() == 2 + cfg=COFACTOR | `determinant(UniMatrix)` — symbolic cofactor |
| var_list.size() == 2 + cfg=DCEI | `dceiDet(MultMatrix)` — real interp |
| var_list.size() == 2 + cfg=DCEIC | `dceiComplexDet(MultMatrix)` — complex interp |

## limitations

- interpolation can drift for high-degree polynomials [?]
- hardcoded epsilon 1e-10 in root-finding strip (Numerical.cpp:292)

## related

- [[sylvester]] — matrix being passed to these det methods
- [[data-flow]] — where DCEI sits in the pipeline
