#include "atom.h"
#include <map>

class Particle {
    public:
        Atom atoms[10];
        int count;

        float eval(std::map<char, float> values) {
            float ans = 1;

            for (int i = 0; i < count; i++) {
                char var = atoms[i].var;
                float value = values[var];
                ans = ans * atoms[i].eval(value);
            }
            
            return ans;
        }

        // * Overload * operator -> p3 = p1 * p2
        Particle operator*(const Particle& p2) {
            Particle p3;
            float coeff = 1;
            int count = 0;
            std::map<char, int> variables;

            // calculating coeff
            for (int i = 0; i < this->count; i++) {
                Atom atom = this->atoms[i];
                char var = atom.var;

                coeff *= atom.coeff;

                if (variables.find(var) == variables.end()) {
                    variables[var] = atom.exp;
                    count++;
                } else { 
                    variables[var] += atom.exp;                 
                }
            }
            for (int i = 0; i < p2.count; i++) {
                Atom atom = p2.atoms[i];
                char var = atom.var;
                coeff *= p2.atoms[i].coeff;

                if (variables.find(var) == variables.end()) {
                    variables[var] = atom.exp;
                    count++;
                } else { 
                    variables[var] += atom.exp;                 
                }
            }

            p3.count = count;

            int i = 0;
            for (std::pair<char, int> pair : variables) {
                p3.atoms[i] = Atom(i == 0 ? coeff : 1, pair.first, pair.second);
                i++;
            }
            
            return p3;
        }
};