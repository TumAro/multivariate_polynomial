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

    float eval(std::map<char, float> values) {
        float ans = 0;

        for (int i = 0; i < polynom.size() ; i++) {
            Particle p = polynom[i];
            ans += p.eval(values);
        };

        return ans;
    }

    void sortLexicographic() {
        std::sort(polynom.begin(), polynom.end(), 
            [](const Particle& a, const Particle& b) {
                return a.isLexGreater(b);
            });
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
                    if (p3.coefficient != 0) {
                        P.polynom[j] = p3;
                    } else {
                        P.polynom.erase(P.polynom.begin() + j);
                    }
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

    // * Overload - operator -> P = P1 - P2 = P1 + (-1*P2)
    Polynomial operator-(const Polynomial& P2) {
        Polynomial result = *this;

        for (const auto& p : P2.polynom) {
            Particle negP = p;
            negP.coefficient = -p.coefficient;

            Polynomial temp;
            temp.addParticle(negP);
            result = result + temp;
        }
        return result;
    }

    // * Overload * Operator -> P = P1*P2
    Polynomial operator*(const Polynomial& P2) {
        Polynomial P;

        for (int i = 0; i < this->polynom.size(); i++) {
            for (int j = 0; j < P2.polynom.size(); j++) {
                Polynomial temp;
                temp.addParticle(this->polynom[i] * P2.polynom[j]);
                P = P + temp;
            }
        }

        return P;
    }

    // * Overload / Operator -> P = Q*D + R
    Polynomial operator/(const Polynomial& divisor) {
        std::cout << "Division started!" << std::endl;
        Polynomial Q;           // Q = 0 -> Quotient
        Polynomial R;           // R = 0 -> Remainder
        Polynomial P = *this;   // P -> copy of this polynom
        Polynomial D = divisor; // D -> copy of divisor

        P.sortLexicographic();
        D.sortLexicographic();

        while (P.polynom.size() > 0) {
            // std::cout << "P size: " << P.polynom.size() << std::endl;
            // std::cout << "Leading term: ";
            // P.print();

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

                // std::cout << "BEFORE subtraction - P size: " << P.polynom.size() << std::endl;

                Polynomial leadTerm;
                leadTerm.addParticle(leadP);
                R = R + leadTerm;
                P = P - leadTerm;

                // std::cout << "AFTER subtraction - P size: " << P.polynom.size() << std::endl;
                // std::cout << "leadTerm was: ";
                // leadTerm.print();
            }
            
        }

        return Q;
    }

    void print() {
        for (int i = 0; i< polynom.size(); i++) {
            Particle p = polynom[i];

            if ( i > 0 && p.coefficient > 0) {
                std::cout << " + ";
            }

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
        std::cout << std::endl;
    }

};