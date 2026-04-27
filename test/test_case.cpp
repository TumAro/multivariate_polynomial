#include "../src/polynomial.h"
#include "../src/linalg.h"
#include "../src/polygraph.h"

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

    PolySystemConfig cfg;
    cfg.final_method = DetMethod::DCEIC;
    PolyGraph graph(cfg);

    auto h1 = graph.input(eq1, {0, 1});      // t1, t2
    auto h2 = graph.input(eq2, {2, 0, 1});   // t3, t1, t2
    auto h3 = graph.input(eq3, {2, 0, 1});   // t3, t1, t2

    auto h4 = graph.eliminate(h2, h3, 2);    // eliminate t3 → result in {t1, t2}
    auto h5 = graph.eliminate(h1, h4, 1);    // eliminate t2 → result in {t1}

    auto h6 = graph.solve(h5);

    auto r = graph.getRoots(h6);

    double eps = 1e-6;

    std::cout << "roots:\n";
    for (auto& root : r) {
        if (std::abs(root.imag()) < eps)
            std::cout << "  t1 = " << root.real() << "\n";
        else
            std::cout << "  t1 = " << root.real() << " + " << root.imag() << "i\n";
    }
}
