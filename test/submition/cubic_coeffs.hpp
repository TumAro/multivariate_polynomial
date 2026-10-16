#pragma once
// Three cubics (total degree <= 3), coefficients ~ U[-2,2] at 4 decimals. Generated once on 2026-10-16 (seed 4), fixed.
#include "../../src/polynomial.h"
#include <vector>

static const std::vector<std::vector<int>> c1_power = {{0,0}, {0,1}, {0,2}, {0,3}, {1,0}, {1,1}, {1,2}, {2,0}, {2,1}, {3,0}};
static const double c1_coeffs[] = {-1.0558, -1.5873, -0.4158, -1.3801, -1.7339, -0.3936, 1.6718, 1.2018, 1.0607, -1.1123};
static const std::vector<std::vector<int>> c2_power = {{0,0,0}, {0,1,0}, {0,2,0}, {0,3,0}, {1,0,0}, {1,1,0}, {1,2,0}, {2,0,0}, {2,1,0}, {3,0,0}};
static const double c2_coeffs[] = {0.1467, -0.8933, -1.3093, -1.5753, -1.1424, 1.7099, 1.3157, 1.2266, 1.2018, -1.2263};
static const std::vector<std::vector<int>> c3_power = {{0,0,0}, {0,0,1}, {0,0,2}, {0,0,3}, {1,0,0}, {1,0,1}, {1,0,2}, {2,0,0}, {2,0,1}, {3,0,0}};
static const double c3_coeffs[] = {-0.7606, 0.5079, 0.9276, 1.4186, 1.5202, -1.6531, 0.4234, 0.6868, 0.0238, -1.2888};
inline void load_eqs(MultPolynom& eq1, MultPolynom& eq2, MultPolynom& eq3) {
    eq1 = MultPolynom(2, 3); for (size_t i = 0; i < c1_power.size(); i++) eq1[c1_power[i]] = c1_coeffs[i];
    eq2 = MultPolynom(3, 3); for (size_t i = 0; i < c2_power.size(); i++) eq2[c2_power[i]] = c2_coeffs[i];
    eq3 = MultPolynom(3, 3); for (size_t i = 0; i < c3_power.size(); i++) eq3[c3_power[i]] = c3_coeffs[i];
}
