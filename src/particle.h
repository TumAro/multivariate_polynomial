#ifndef PARTICLE_H
#define PARTICLE_H

#include "atom.h"
#include <vector>
#include <map>

class Particle {
    public:
        std::vector<Atom> atoms;

        float coefficient;
        std::map<char, int> variables;

        Particle() : coefficient(1) {}
        Particle(const Atom& atom) : coefficient(1) {
            addAtom(atom);
        }

        void addAtom(Atom atom) {
            this->coefficient *= atom.coeff;
            atoms.push_back(Atom(1, atom.var, atom.exp));
            mapVars();
        }

        void mapVars () {
            variables.clear();

            for (int i = 0; i < atoms.size(); i++) {
                Atom atom = atoms[i];
                char var = atom.var;
                if (atom.exp == 0) {
                    var = '@';
                }

                
                if (variables.find(var) == variables.end()) {
                    variables[var] = atom.exp;
                } else { 
                    variables[var] += atom.exp;                 
                }
            }
            this->variables = variables;
        }

        // evaluation
        float operator()(std::map<char, float> values) const {
            float ans = this->coefficient;

            for (int i = 0; i < atoms.size(); i++) {
                char var = atoms[i].var;
                float value = values[var];
                ans = ans * atoms[i](value);
            }
            
            return ans;
        }

        Particle partialEval(std::map<char, float> values) const {
            Particle p;
            p.coefficient = this->coefficient;

            for (const Atom& atom: this->atoms) {
                char var = atom.var;
                if(values.find(var) != values.end()) {
                    p.coefficient  *= atom(values[var]);
                }
                else {
                    p.addAtom(atom);
                }
            }

            return p;
        }

        std::vector<float> getExpVec() const { 
            std::vector<float> expVec;

            for (const auto& pair : this->variables) {
                expVec.push_back(pair.second);
            }

            return expVec;
        }

        bool isLexGreater(const Particle& p2) const {
            std::vector<float> V = this->getExpVec();
            std::vector<float> W = p2.getExpVec();

            std::vector<float> resultant;

            int maxLen = std::max(V.size(), W.size());

            for (int i = 0; i < maxLen; i++) {
                float v = (i < V.size()) ? V[i] : 0;
                float w = (i < W.size()) ? W[i] : 0;

                resultant.push_back(v - w);
            }

            for (int i = 0; i < resultant.size(); i++) {
                if (resultant[i] != 0) {
                    return resultant[i] > 0;
                }
            }
            return false;
        }

        // * Overload * operator -> p = p1 * p2
        Particle operator*(const Particle& p2) const {
            Particle p;
            float coeff = this->coefficient * p2.coefficient;;
            std::map<char, int> variables;

            // calculating coeff
            for (int i = 0; i < this->atoms.size(); i++) {
                Atom atom = this->atoms[i];
                char var = atom.var;

                coeff *= atom.coeff;

                if (variables.find(var) == variables.end()) {
                    variables[var] = atom.exp;
                } else { 
                    variables[var] += atom.exp;                 
                }
            }
            for (int i = 0; i < p2.atoms.size(); i++) {
                Atom atom = p2.atoms[i];
                char var = atom.var;
                coeff *= p2.atoms[i].coeff;

                if (variables.find(var) == variables.end()) {
                    variables[var] = atom.exp;
                } else { 
                    variables[var] += atom.exp;                 
                }
            }


            int i = 0;
            for (std::pair<char, int> pair : variables) {
                p.addAtom(Atom(i == 0 ? coeff : 1, pair.first, pair.second));
                i++;
            }
            
            return p;
        }

        Particle operator*(const Atom& a2) const {
            Particle p = *this;
            p.addAtom(a2);
            return p;
        }

        Particle operator*(float b) const {
            Particle p = *this;
            p.coefficient *= b;
            return p;
        }

        // * Overload / operator -> p = p1 / p2
        Particle operator/(const Particle& p2) const {
            std::map<char, float> vars;
            
            float coeff = this->coefficient / p2.coefficient;

            for (const auto& pair: this->variables) {
                char var = pair.first;
                float exp1 = pair.second;
                float exp2 = (p2.variables.count(var) > 0) ? p2.variables.at(var) : 0;
                vars[var] = exp1 - exp2;
            }

            for (const auto& pair : p2.variables) {
                char var = pair.first;
                if (this->variables.count(var) == 0) {
                    vars[var] = 0 - pair.second;
                }
            }

            Particle p;
            int i = 0;
            for (const auto pair: vars) {
                p.addAtom(Atom(
                    i == 0 ? coeff : 1,
                    pair.first,
                    pair.second
                ));
                i++;
            }

            return p;
        }

        Particle operator/(const Atom&a2) const {
            Particle p = *this;
            Atom inv = 1 / a2;

            p.addAtom(inv);
            return p;
        }

        Particle operator/(float b) const {
            Particle p = *this;
            p.coefficient /= b;
            return p;
        }

        // * Overload == operator (p1==p2)
        bool operator==(const Particle& p2) const {
            if (
                this->coefficient != p2.coefficient ||
                this->variables != p2.variables 
            ) { return false; }

            return true;
        }

        // * Overload unary negeion -p
        Particle operator-()  {
            Particle p = *this;
            p.coefficient = -p.coefficient;
            return p;
        }

        void print() const {
            std::cout << coefficient;
            for (auto pair : variables) {
                if (pair.second != 0) {
                    std::cout << pair.first;
                    if (pair.second != 1) {
                        std::cout << "^" << pair.second;
                    }
                }
            }
            std::cout << std::endl;
        }
};

Particle operator*(const Atom&a, const Atom&b) {
    Particle p;
    if (a.var == b.var) {
        Atom result(
            a.coeff * b.coeff,
            a.var,
            a.exp + b.exp
        );
        p.addAtom(result);
    } else {
        p.addAtom(a);
        p.addAtom(b);
    }
    return p;
}

Particle operator*(const Atom&a1, const Particle&p2) {
    Particle p = p2;
    p.addAtom(a1);
    return p;
}

Particle operator*(float a, const Particle&p2) {
    Particle p = p2;
    p.coefficient *= a;
    return p;
}


Particle operator/(const Atom&a, const Atom&b) {
    Particle p;
    if (a.var == b.var) {
        Atom result(a.coeff / b.coeff, a.var, a.exp - b.exp);
        p.addAtom(result);
    } else {
        Atom invb = 1 / b;
        p.addAtom(a);
        p.addAtom(invb);
    }
    return p;
}

Particle operator/(float a, const Particle&p2) {
    Particle numerator;
    numerator.coefficient = a;
    return numerator / p2;
}

Particle operator/(const Atom&a1, const Particle&p2) {
    Particle p = 1 / p2;
    p.addAtom(a1);
    return p;
}

#endif