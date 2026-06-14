#include "../../src/polynomial.h"
#include "../../src/linalg.h"
#include "../../src/polygraph.h"
#include "coeffs.hpp"

int main() {
    MultPolynom eq1, eq2, eq3;
    load_eqs(eq1, eq2, eq3);

    PolySystemConfig cfg;
    cfg.final_method = DetMethod::DCEIC;
    PolyGraph graph(cfg);

    auto h1 = graph.input(eq1, {0, 1});
    auto h2 = graph.input(eq2, {2, 0, 1});
    auto h3 = graph.input(eq3, {2, 0, 1});

    auto h4 = graph.eliminate(h2, h3, 2);
    auto h5 = graph.eliminate(h1, h4, 1);
    auto h6 = graph.solve(h5);

    auto t1_roots = graph.getRoots(h6);

    double eps = 1e-6;

    for (auto& t1 : t1_roots) {
        if (std::abs(t1.imag()) >= eps) continue;
        double t1_val = t1.real();

        auto t2_poly = UniPolynom(eq1.partialEval(0, t1_val));
        for (auto& t2 : roots(t2_poly)) {
            if (std::abs(t2.imag()) >= eps) continue;
            double t2_val = t2.real();

            auto t3_poly = UniPolynom(eq2.partialEval(1, t1_val).partialEval(1, t2_val));
            for (auto& t3 : roots(t3_poly)) {
                if (std::abs(t3.imag()) >= eps) continue;
                std::cout << "t1=" << t1_val << "  t2=" << t2_val << "  t3=" << t3.real() << "\n";
            }
        }
    }
}
