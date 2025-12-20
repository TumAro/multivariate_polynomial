#include <vector>
#include <algorithm>

#ifndef IOHANDLER_H
#define IOHANDLER_H

#include "polynomial.h"

inline Polynomial ArrayToPoly (const  std::vector<float> coefficients, const char var, int max_degree = -1) {
    if (max_degree == -1) {
        max_degree = coefficients.size() - 1;
    }
    Polynomial P(max_degree, var);

    int bound = std::min((int)coefficients.size(), max_degree + 1);
    
    for (int i = 0; i < bound; i++) {
        float coeff = coefficients[i];
        if (coeff != 0) {
            Particle p(Atom(coefficients[i],var,i));
            P.addParticle(p);
        }
    }

    return P;
}

inline std::vector<float> PolyToArray(const Polynomial P, const char var) {

    int arraySize;
    if (P.max_degree != -1) {
        arraySize = P.max_degree;
    } else {
        arraySize = 0;
        for (const Particle& particle : P.polynom) {
            if (particle.variables.count(var) > 0) {
                float power = particle.variables.at(var);
                if (power > arraySize) arraySize = power;
            }
        }
    }

    std::vector<float> coefficients(arraySize+1, 0.0);

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

#endif