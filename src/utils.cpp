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