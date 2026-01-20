#include "utils.h"

void Log(std::string txt) {
    std::cout << txt << std::endl;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

double pow(double base, int exp) {
    if (exp == 0) return 1;
    
    double result = 1;
    bool neg = exp < 0;
    if (neg) exp = -exp;

    for (int i = 0; i < exp; i++) {
        result *= base;
    }

    return neg ? 1.0/result : result;
}

std::vector<float> joinVectors(std::vector<float> vec1, std::vector<float> vec2) {
    int size1 = vec1.size();
    int size2 = vec2.size();

    std::vector<float> result(size1 + size2);
    
    for (int i = 0; i < size1; i++) {
        result[i] = vec1[i];
    }

    for (int i = 0; i < size2; i++) {
        result[size1 + i] = vec2[i];
    }

    return result;
}