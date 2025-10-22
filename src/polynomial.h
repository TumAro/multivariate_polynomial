#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <algorithm>
#include "particle.h"


class Polynomial {
    public:
    std::vector<Particle> polynom;

    Polynomial() {}

    void addParticle(Particle p) {
        polynom.push_back(p);
    }

    // evaluation
    float operator()(std::map<char, float> values) {
        float ans = 0;

        for (int i = 0; i < polynom.size() ; i++) {
            Particle p = polynom[i];
            ans += p(values);
        };

        return ans;
    }

    Polynomial partialEval(std::map<char, float> values) {
        Polynomial P;

        for (const Particle& particle: polynom) {
            Particle p = particle.partialEval(values);
            P = P + p;
        }

        return P;
    }

    void sortLexicographic() {
        std::sort(polynom.begin(), polynom.end(), 
            [](const Particle& a, const Particle& b) {
                return a.isLexGreater(b);
            });
    }

    // * Unary negation
    Polynomial operator-() {
        Polynomial P;
        for (const auto& particle : this->polynom) {
            Particle p = particle;
            P.addParticle(-p);
        }

        return P;
    }

    // * Overload + operator -> P = P1 + P2
    Polynomial operator+(const Polynomial& P2) {
        Polynomial P = *this;
        for (const Particle& particle : P2.polynom) {
            P = P + particle;
        }
        
        return P;
    }

    // * (+)particle
    Polynomial operator+(const Particle& p) {
        Polynomial P = *this;

        bool found = false;
        for (auto& particle : P.polynom) {
            if (particle.variables == p.variables) {
                particle.coefficient += p.coefficient;
                found = true;
            }
        }

        if (!found) {
            P.addParticle(p);
        }

        return P;
    }

    Polynomial operator-(const Particle& p) {
        Particle particle = p;
        return *this + (-particle);
    }

    // * (+)atom
    Polynomial operator+(const Atom& a) {
        Particle p;
        p.addAtom(a);
        return *this + p;
    }

    Polynomial operator+(float f) {
        return *this + Atom(f,'@', 0);
    }

    Polynomial operator-(const Atom& a) {
        Particle p;
        p.addAtom(a);
        return *this - p;
    }

    Polynomial operator-(float f) {
        Polynomial P = *this;
        return P - Atom(f,'@', 0);
    }

    // * Overload - operator -> P = P1 - P2 = P1 + (-1*P2)
    Polynomial operator-(const Polynomial& P2) {
        Polynomial polynom = P2;
        return *this + (-polynom);
    }

    // * Overload * Operator -> P = P1*P2
    Polynomial operator*(const Polynomial& P2) {
        Polynomial P ;
        for (const auto& particle : P2.polynom) {
            P = P + *this * particle;
        }
        return P;
    }

    // * (*)particle
    Polynomial operator*(const Particle&p) {
        Polynomial P = *this;

        for (auto& particle : P.polynom){
            particle = particle * p;
        }

        return P;
    }

    // * (*)atom
    Polynomial operator*(const Atom& a) {
        Particle p;
        p.addAtom(a);
        return *this * p;
    }

    Polynomial operator*(float f) {
        return *this * Atom(f, '@', 0);
    }

    // * Overload / Operator -> P = Q*D + R -> Q
    Polynomial operator/(const Polynomial& divisor) {
        std::cout << "Division started!" << std::endl;
        Polynomial Q;           // Q = 0 -> Quotient
        Polynomial R;           // R = 0 -> Remainder
        Polynomial P = *this;   // P -> copy of this polynom
        Polynomial D = divisor; // D -> copy of divisor

        P.sortLexicographic();
        D.sortLexicographic();

        while (P.polynom.size() > 0) {

            Particle leadP = P.polynom[0];
            Particle leadD = D.polynom[0];
            bool divisible = true;

            for (const auto& pair : leadD.variables) {
                char var = pair.first;
                if (leadP.variables.count(var) > 0) {
                    divisible = leadP.variables[var] >= pair.second;
                } else { divisible = false; }
                if (!divisible) {break;}
            }

            if (divisible) {
                Polynomial q;
                q.addParticle(leadP / leadD);
                Q = Q + q;
                P = P - (q * D);
            } else {
                Polynomial leadTerm;
                leadTerm.addParticle(leadP);
                R = R + leadTerm;
                P = P - leadTerm;
            }
            
        }

        return Q;
    }

    // * Overload % Operator -> P = Q*D + R -> R
    Polynomial operator%(const Polynomial& divisor) {
        return *this - ((*this / divisor) * divisor);
    }

    void print() {
        for (int i = 0; i< polynom.size(); i++) {
            Particle p = polynom[i];

            if ( i > 0 && p.coefficient > 0) {
                std::cout << " + ";
            }

            if (p.coefficient != 0) {
                std::cout << p.coefficient;

                for (auto pair : p.variables) {
                    if (pair.second !=0) {
                            std::cout << pair.first;
                        if (pair.second != 1) {
                            std::cout << "^" << pair.second;
                        }
                    }
                }
            }
            
        }
        std::cout << std::endl;
    }

};

// * (+)atom - operation overloading
Polynomial operator+(const Atom& a, const Atom& b) {
    Polynomial P;
    P = P + a;
    P = P + b;
    return P;
}

Polynomial operator+(const Atom& a, const Polynomial& P2) {
    Polynomial P = P2;
    return P + a;
}

Polynomial operator+(float f, const Polynomial& P2) {
    Polynomial P = P2;
    return P + f;
}

Polynomial operator-(const Atom& a, const Atom& b) {
    Polynomial P;
    P = P + a;
    P = P - b;
    return P;
}

Polynomial operator-(const Atom& a, const Polynomial& P2) {
    Polynomial P = P2;
    return a - P;
}

Polynomial operator-(float f, const Polynomial& P2) {
    Polynomial P = P2;
    return -P + f;
}

// * (*)atom
Polynomial operator*(const Atom& a, const Polynomial& P2) {
    Polynomial P = P2;
    return P * a;
}

Polynomial operator*(float f, const Polynomial& P2) {
    Polynomial P = P2;
    return P * f;
}

// * (+)Particle - operation overloading
Polynomial operator+(const Particle& p, const Particle& q) {
    Polynomial P;
    P = P + p;
    P = P + q;
    return P;
}

Polynomial operator+(const Particle& p, const Polynomial& P2) {
    Polynomial P = P2;
    return P + p;
}

Polynomial operator-(const Particle& p, const Particle& q) {
    Polynomial P;
    P = P + p;
    P = P - p;
    return P;
}

Polynomial operator-(const Particle& p, const Polynomial& P2) {
    Polynomial P = P2;
    return -P + p;
}

// * (*)Particle
Polynomial operator*(const Particle& p, const Polynomial& P2) {
    Polynomial P = P2;
    return P * p;
}

// * ========================================================
// * ========================================================

#endif