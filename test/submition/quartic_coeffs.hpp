#pragma once
#include "../../src/polynomial.h"
#include <vector>

// Generated once on 2026-10-15 (seed 20261015), fixed. Coeffs ~ U[-2,2], 4 decimals, total degree <= 4.

// eq1: {t1, t2}
static const std::vector<std::vector<int>> c1_power = {
    {0,0}, {0,1}, {0,2}, {0,3}, {0,4}, {1,0}, {1,1}, {1,2}, {1,3}, {2,0}, {2,1}, {2,2}, {3,0}, {3,1}, {4,0}
};
static const double c1_coeffs[] = {
    1.6574, -1.2062, -0.0761, 1.2798, -1.8388, 0.4402, 0.1007, -0.3099, -0.4170, 0.6104, 1.9212, 0.5248, 0.6125, 1.9806, 1.3225
};

// eq2: {t3, t1, t2}
static const std::vector<std::vector<int>> c2_power = {
    {0,0,0}, {0,1,0}, {0,2,0}, {0,3,0}, {0,4,0}, {1,0,0}, {1,1,0}, {1,2,0}, {1,3,0}, {2,0,0}, {2,1,0}, {2,2,0}, {3,0,0}, {3,1,0}, {4,0,0}
};
static const double c2_coeffs[] = {
    1.1588, -0.0094, 1.4101, -1.7677, -1.0633, -1.2801, 1.9631, -0.9153, -0.5949, 1.7206, -0.9199, -0.4366, 1.3908, -1.8182, 1.2589
};

// eq3: {t3, t1, t2}
static const std::vector<std::vector<int>> c3_power = {
    {0,0,0}, {0,0,1}, {0,0,2}, {0,0,3}, {0,0,4}, {1,0,0}, {1,0,1}, {1,0,2}, {1,0,3}, {2,0,0}, {2,0,1}, {2,0,2}, {3,0,0}, {3,0,1}, {4,0,0}
};
static const double c3_coeffs[] = {
    1.6983, 1.2058, 0.1506, -0.2992, 1.5446, 0.5839, 0.6407, -0.0146, -1.5426, -1.7227, -1.2378, -1.8513, -0.2362, 1.5209, -1.1844
};

inline void load_eqs(MultPolynom& eq1, MultPolynom& eq2, MultPolynom& eq3) {
    eq1 = MultPolynom(2, 4);
    for (size_t i = 0; i < c1_power.size(); i++) eq1[c1_power[i]] = c1_coeffs[i];
    eq2 = MultPolynom(3, 4);
    for (size_t i = 0; i < c2_power.size(); i++) eq2[c2_power[i]] = c2_coeffs[i];
    eq3 = MultPolynom(3, 4);
    for (size_t i = 0; i < c3_power.size(); i++) eq3[c3_power[i]] = c3_coeffs[i];
}
