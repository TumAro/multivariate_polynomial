#include <vector>
#include "particle.h"

class Polynomial {
    public:
    std::vector<Particle> polynom;

    Polynomial() {}

    void addParticle(Particle p) {
        polynom.push_back(p);
    }

    float eval(std::map<char, float> values) {
        float ans = 0;

        for (int i = 0; i < polynom.size() ; i++) {
            Particle p = polynom[i];
            ans += p.eval(values);
        };

        return ans;
    }

    // * Overload + operator -> P = P1 + P2
    Polynomial operator+(const Polynomial& P2) {
        Polynomial P;
        
        P.polynom = this->polynom;

        for (int i = 0; i < P2.polynom.size() ; i++) {
            bool match = false;
            Particle p2 = P2.polynom[i];

            for (int j = 0; j < P.polynom.size(); j++) {
                Particle p1 = P.polynom[j];

                if (p2.variables == p1.variables) {
                    Particle p3 = p1 + p2;
                    P.polynom[j] = p3;
                    match = true;
                    break;
                }
            }

            if (!match) {
                P.polynom.push_back(p2);
            }
        }

        return P;
    }

};