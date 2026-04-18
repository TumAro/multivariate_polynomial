#include "../src/polynomial.h"
#include "../src/linalg.h"

int main() {
    // t1=x, t2=y, t3=z

    double c1[] = {
         0.5399303056689184, -0.1112430358185238,  2.284955558838335,
         0.1112430358185238, -0.9799999999999999,  0.1112430358185238,
        -0.22509494750049885,-0.1112430358185238,  0.5399303056689182
    };

    // eq2, eq3 are 3-var with t3 at pos0: idx = e_t3 + 3*e_t1 + 9*e_t2
    double c2[] = {
         0.6471366643508364,  1.0674608184676306,  0.32589362853231196,
        -1.0674608184676306, -0.9799999999999999, -1.0674608184676306,
         1.9483797001693595,  1.0674608184676306,  0.6471366643508359,
         0,0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,0
    };

    double c3[] = {
         0.2969872981077808,  0.956217782649107,   1.2307695154586735,
         0,0,0, 0,0,0,
        -0.9562177826491068, -0.9799999999999999, -0.9562177826491068,
         0,0,0, 0,0,0,
         0.3432050807568875,  0.956217782649107,   0.2969872981077808,
         0,0,0, 0,0,0
    };

    // eq1 with t2 at pos0 (swapped from c1) for the final resultant step
    double c1s[] = {
         0.5399303056689184,  0.1112430358185238, -0.22509494750049885,
        -0.1112430358185238, -0.9799999999999999, -0.1112430358185238,
         2.284955558838335,   0.1112430358185238,  0.5399303056689182
    };

    MultPolynom eq1(2, 2);  eq1.set(std::vector<double>(c1,  c1  + 9));
    MultPolynom eq2(3, 2);  eq2.set(std::vector<double>(c2,  c2  + 27));
    MultPolynom eq3(3, 2);  eq3.set(std::vector<double>(c3,  c3  + 27));

    // res1 = Res_t3(eq2, eq3)  ->  polynomial in (t1, t2)
    MultPolynom res1 = determinant(sylvesterMat(eq2, eq3));

    // swap res1 from (pos0=t1, pos1=t2) to (pos0=t2, pos1=t1), trim to deg 4
    MultPolynom res1s(2, 4);
    for (int e0 = 0; e0 <= 4; e0++)
        for (int e1 = 0; e1 <= 4; e1++)
            res1s[{e1, e0}] = res1[{e0, e1}];

    MultPolynom eq1s(2, 2); eq1s.set(std::vector<double>(c1s, c1s + 9));

    // final = Res_t2(eq1, res1)  ->  polynomial in t1
    UniPolynom final_poly = dceiComplexDet(sylvesterMat(eq1s, res1s));
    std::cout << "final: "; final_poly.print(); std::cout << "\n";
}
