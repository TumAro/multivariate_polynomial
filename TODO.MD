## Current Task

**ATOMS**
- [x] multiplicative inverse
- [x] equality test
- [x] mult operator


**Particle**
- [x] multiply by atom
- [x] divide by atom
- [x] structural equality
- [x] negate operation (unary)
- [x] Particle = atom * atom (when different var)


**Polynom**
- [x] Polynom unary negetion
- [x] Polynom (+, -, *) atom
- [x] Polynom (+, -, *) particle
- [x] partial evaluation (substitue some vars)
- [x] Polynom = particle + particle (when different varmap)
- [x] Polnom = atom + atom (when different vars)
- [x] Polynom -> degree, leading term
- [ ] Equality check
- [ ] Number of variables

**Input Output**
- [x] array -> polynom (univariate)
- [x] polynom -> array (univariate)
- [ ] lexicographic scale up

**LA**
- [x] Polynom matrix struct

**Determinant**
- [x] 2x2 det
- [x] 3x3 det
- [x] ?scale up to larger det?
- [x] recursive cofactor

- [ ] Matrix (+, -, *)
- [ ] Transpose

- [ ] LU decompostion

## LATER
 
[ ] - !real number inputs
[ ] - precision on float values
[ ] - Kronecker mult (if speed needed)  
[ ] - boost library to precision and enchancment
[ ] - Growbner basis operation  
[ ] - Lin Transform  
[ ] - Resultant of Polynomials  

# HIGH PRIORITY - UNIVARIATE IO ROBUSTNESS

## ✓ COMPLETED: Polynomial degree bounding infrastructure
- [x] Added `max_degree` and `primary_var` members to Polynomial class
- [x] Added constructor `Polynomial(int degree, char var)` for bounded polynomials
- [x] Updated all operators to preserve/merge/add degree bounds correctly
- [x] `addParticle()` now enforces degree bounds automatically

## REMAINING: IOhandler integration
- [ ] Update `ArrayToPoly()` to auto-detect max_degree from array size
- [ ] Handle oversized arrays: [1,1,1,1,2] with implied degree 4 → auto-caps at array length - 1
- [ ] Add optional max_degree parameter to ArrayToPoly for explicit capping
- [ ] Update `PolyToArray()` to respect max_degree if set (or calculate from actual polynomial)
- [ ] Add `ArrayToMatrix(nested_array)` → quick matrix init like [[[1,0],[2,3]], [[2,1], [1,3]]]

## REMAINING: Utility methods for Polynomial class
- [x] Add `getDegree()` → return actual highest degree in polynomial (scan particles)
- [x] Add `getLeadingTerm()` → return leading particle after sort
- [ ] Add `operator==` → equality check between polynomials
- [ ] Add `getNumVariables()` → count unique variables in polynomial
- [ ] Auto-sort lexicographically after operations (optional - discuss first)

## Testing checklist
- [ ] Test: `ArrayToPoly({1,0,2}, 'x')` → creates P with degree 2, contains 1+2x^2
- [ ] Test: `ArrayToPoly({1,1}, 'x')` → creates P with degree 1, contains 1+x
- [ ] Test: `ArrayToPoly({1,1,1,1,2}, 'x', 3)` → creates P with degree 3, caps to 1+x+x^2+x^3
- [ ] Test: Bounded polynomial operations preserve bounds correctly
- [ ] Test: Matrix quick-init from nested array
- [ ] Test: Lexicographic ordering persists/works correctly