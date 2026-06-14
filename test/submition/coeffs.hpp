#pragma once
#include "../../src/polynomial.h"
#include <vector>

// eq1: {t1, t2}
static const std::vector<std::vector<int>> c1_power = {
    {0,0},{1,0},{2,0},
    {0,1},{1,1},{2,1},
    {0,2},{1,2},{2,2}
};
static const double c1_coeffs[] = {
     0.5399303056689184, -0.1112430358185238,  2.284955558838335,
     0.1112430358185238, -0.9799999999999999,  0.1112430358185238,
    -0.22509494750049885,-0.1112430358185238,  0.5399303056689182
};

// eq2: {t3, t1, t2}
static const std::vector<std::vector<int>> c2_power = {
    {0,0,0},{0,1,0},{0,2,0},
    {1,0,0},{1,1,0},{1,2,0},
    {2,0,0},{2,1,0},{2,2,0}
};
static const double c2_coeffs[] = {
     0.6471366643508364, -1.0674608184676306,  1.9483797001693595,
     1.0674608184676306, -0.9799999999999999,  1.0674608184676306,
     0.32589362853231196,-1.0674608184676306,  0.6471366643508359
};

// eq3: {t3, t1, t2}
static const std::vector<std::vector<int>> c3_power = {
    {0,0,0},{0,0,1},{0,0,2},
    {1,0,0},{1,0,1},{1,0,2},
    {2,0,0},{2,0,1},{2,0,2}
};
static const double c3_coeffs[] = {
     0.2969872981077808, -0.9562177826491068,  0.3432050807568875,
     0.956217782649107,  -0.9799999999999999,  0.956217782649107,
     1.2307695154586735, -0.9562177826491068,  0.2969872981077808
};

inline void load_eqs(MultPolynom& eq1, MultPolynom& eq2, MultPolynom& eq3) {
    eq1 = MultPolynom(2, 4);
    for (int i = 0; i < 9; i++) eq1[c1_power[i]] = c1_coeffs[i];

    eq2 = MultPolynom(3, 4);
    for (int i = 0; i < 9; i++) eq2[c2_power[i]] = c2_coeffs[i];

    eq3 = MultPolynom(3, 4);
    for (int i = 0; i < 9; i++) eq3[c3_power[i]] = c3_coeffs[i];
}
