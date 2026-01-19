#pragma once

#include <cmath>
#include <stdexcept>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

// ============================================================================
// Atom class - represents a single term like 3x^2
// ============================================================================
class Atom {
public:
    float coeff;
    float exp;
    char var;

    // Constructors
    Atom();
    Atom(float a, char v, float e);

    // Inline getter - simple enough to stay in header
    float getCoeff() const {
        return coeff;
    }

    // Member operators
    float operator()(float x) const;
    Atom operator/(float b) const;
    Atom operator*(float b) const;
    bool operator==(const Atom& b) const;
};

// Free function declarations for Atom
Atom operator/(float a, const Atom& b);
Atom operator*(float a, const Atom& b);

// Forward declare Polynomial for Particle
class Polynomial;

// ============================================================================
// Particle class - represents a product of atoms like 3x^2*y^3
// ============================================================================
class Particle {
public:
    std::vector<Atom> atoms;
    float coefficient;
    std::map<char, int> variables;

    // Constructors
    Particle();
    Particle(const Atom& atom);

    // Member functions
    void addAtom(Atom atom);
    void mapVars();
    float operator()(std::map<char, float> values) const;
    Polynomial partialEval(std::map<char, float> values) const;
    std::vector<float> getExpVec() const;
    bool isLexGreater(const Particle& p2) const;
    void print() const;

    // Member operators
    Particle operator*(const Particle& p2) const;
    Particle operator*(const Atom& a2) const;
    Particle operator*(float b) const;
    Particle operator/(const Particle& p2) const;
    Particle operator/(const Atom& a2) const;
    Particle operator/(float b) const;
    bool operator==(const Particle& p2) const;
    Particle operator-();
};

// Free function declarations for Particle
Particle operator*(const Atom& a, const Atom& b);
Particle operator*(const Atom& a1, const Particle& p2);
Particle operator*(float a, const Particle& p2);
Particle operator/(const Atom& a, const Atom& b);
Particle operator/(float a, const Particle& p2);
Particle operator/(const Atom& a1, const Particle& p2);

// ============================================================================
// Polynomial class - represents a sum of particles
// ============================================================================
class Polynomial {
public:
    std::vector<Particle> polynom;
    int max_degree;
    char primary_var;

    // Constructors
    Polynomial();
    Polynomial(int degree, char var);

    // Member functions
    void addParticle(Particle p);
    float operator()(std::map<char, float> values);
    Polynomial partialEval(std::map<char, float> values);
    void sortLexicographic();
    int getDegree(char var) const;
    Particle getLead();
    void print() const;

    // Unary operators
    Polynomial operator-() const;

    // Polynomial + operations
    Polynomial operator+(const Polynomial& P2) const;
    Polynomial operator+(const Particle& p) const;
    Polynomial operator+(const Atom& a) const;
    Polynomial operator+(float f) const;

    // Polynomial - operations
    Polynomial operator-(const Polynomial& P2) const;
    Polynomial operator-(const Particle& p) const;
    Polynomial operator-(const Atom& a) const;
    Polynomial operator-(float f) const;

    // Polynomial * operations
    Polynomial operator*(const Polynomial& P2) const;
    Polynomial operator*(const Particle& p) const;
    Polynomial operator*(const Atom& a) const;
    Polynomial operator*(float f) const;

    // Polynomial / and % operations
    Polynomial operator/(const Polynomial& divisor) const;
    Polynomial operator%(const Polynomial& divisor) const;
};

// Free function declarations for Polynomial
Polynomial operator+(const Atom& a, const Atom& b);
Polynomial operator+(const Atom& a, const Polynomial& P2);
Polynomial operator+(float f, const Polynomial& P2);
Polynomial operator-(const Atom& a, const Atom& b);
Polynomial operator-(const Atom& a, const Polynomial& P2);
Polynomial operator-(float f, const Polynomial& P2);
Polynomial operator*(const Atom& a, const Polynomial& P2);
Polynomial operator*(float f, const Polynomial& P2);
Polynomial operator+(const Particle& p, const Particle& q);
Polynomial operator+(const Particle& p, const Polynomial& P2);
Polynomial operator-(const Particle& p, const Particle& q);
Polynomial operator-(const Particle& p, const Polynomial& P2);
Polynomial operator*(const Particle& p, const Polynomial& P2);
