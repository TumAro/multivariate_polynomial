# concepts/coeff-indexing

## what

MultPolynom stores coefficients in a flat `vector<float>` using lexicographic (graded lex) order.
size = `binomial(deg+vars, vars)` — NOT `(deg+1)^vars`.

## why binomial, not power

only stores monomials with total degree ≤ deg.
e.g. vars=2, deg=2: all (a,b) s.t. a+b ≤ 2 → C(4,2)=6 terms, not 3²=9.

**IMPORTANT**: old documentation (MULTPOLYNOM_USAGE.md) incorrectly says size=(deg+1)^vars.
actual impl uses binomial. source: Multivariate.cpp:10.

## index ↔ exponent mapping

### exp → index (used in `operator[]`)
```
idx = 0, budget = deg
for i = vars-1 downto 1:
    k = exp[i]
    idx += C(budget+i+1, i+1) - C(budget-k+i+1, i+1)
    budget -= k
idx += exp[0]
```
src: Multivariate.cpp:144

### index → exp (used in `index2exp`)
```
for n = vars downto 2:
    k = 0
    while rem >= C(budget-k+n-1, n-1):
        rem -= C(budget-k+n-1, n-1)
        k++
    indices[n-1] = k
    budget -= k
indices[0] = rem
```
src: Multivariate.cpp:126

## example: vars=2, deg=2

| idx | exp [x,y] | monomial |
|-----|-----------|----------|
| 0 | [0,0] | 1 |
| 1 | [1,0] | x |
| 2 | [2,0] | x² |
| 3 | [0,1] | y |
| 4 | [1,1] | xy |
| 5 | [0,2] | y² |

total: 6 = C(4,2). not 9.

## implications for coeff() and Sylvester

`MultPolynom::coeff(var_idx, exp)` iterates all coefficients, filters by `exp[var_idx]==exp`, builds sub-poly with remaining vars.
used heavily in `sylvesterMat` to extract row entries of Sylvester matrix.

## related

- [[classes]] — MultPolynom full class doc
- [[sylvester]] — uses coeff() to build matrix entries
