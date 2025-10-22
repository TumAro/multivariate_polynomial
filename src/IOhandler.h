#include <vector>
#include <algorithm>
#include "polynomial.h"

Polynomial ArrayToPoly (const  std::vector<float> coefficients, const char var) {
    Polynomial P;
    
    for (int i = 0; i < coefficients.size(); i++) {
        float coeff = coefficients[i];
        if (coeff != 0) {
            Particle p(Atom(coefficients[i],var,i));
            P.addParticle(p);
        }
    }

    return P;
}

std::vector<float> PolyToArray(const Polynomial P, const char var) {
    int maxPower = 0;

    for (const Particle& particle : P.polynom) {
        if (particle.variables.count(var) > 0) {
            float power = particle.variables.at(var);
            if (power >maxPower) maxPower = power;
        }
    }

    std::vector<float> coefficients(maxPower+1, 0.0);

    for (const Particle& particle : P.polynom) {
        if (particle.variables.count(var) > 0) {
            int power = particle.variables.at(var);
            coefficients[power] = particle.coefficient;
        } else if (particle.variables.count('@') > 0) { 
            coefficients[0] = particle.coefficient;
        }
        
    }

    return coefficients;
}