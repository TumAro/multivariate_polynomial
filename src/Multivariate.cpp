#include "polynomial.h"

// constructors
MultPolynom::MultPolynom(int var, std::vector<int>& degrees) {
        this->vars = var;
        this->degrees = degrees;
        int size = 1;

        for (const auto& val : degrees) {
            size *= val+1;
        }

        this->coeffs.resize(size);
    }
