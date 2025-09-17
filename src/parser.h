#include <string>
#include <regex>

#include "polynomial.h"


Atom parseAtom(std::string term) {

    std::regex pattern(R"((\d+\.?\d*)\*?([a-zA-Z])\^?(\d+\.?\d*))");
    std::smatch m;

    std::regex_search(term, m, pattern);

    float coeff = std::stof(m[1].str());
    char var = m[2].str()[0];
    float exp = std::stof(m[3].str());

    return Atom(coeff, var, exp);
}

Polynomial parsePolynom(std::string poly) {
    std::vector<std::string> tokens;
    std::regex pattern(R"(([^+-]+)|([+-]))");

    std::sregex_iterator begin(poly.begin(), poly.end(), pattern);
    std::sregex_iterator end;

    for (auto i = begin; i != end; i++) {
        std::string token = i->str();

        token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    Polynomial P;

    for (int i = 0; i < tokens.size(); i++) {
        std::string value = tokens[i];
        Polynomial tempPolynom;

        if (value != "+" && value != "-") {
            Particle p;
            p.addAtom(parseAtom(value));
            tempPolynom.addParticle(p);
        }

    }

}