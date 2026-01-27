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

int factorial(int n) {
    if (n < 0 ) return -1;

    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
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


// TOTAL = MAX DEGREE
// REMAINING_POS = Number of VARIABLES
std::vector<std::vector<int>> lexorderArray(int total, int remainder_pos, std::vector<int> indices, int pos) {
    if (indices.empty()) {
        indices.resize(remainder_pos);  // Initialize on first call
    }
    
    std::vector<std::vector<int>> all_sequences;
    
    if (remainder_pos==1 && total >= 0) {
        // return [n]
        indices[pos] = total;
        all_sequences.push_back(indices);
        return all_sequences;
    }

    for (int i = total; i >= 0; i--) {
        // solve for lexorderArray(n-i, k-1)
        indices[pos] = i;
        std::vector<std::vector<int>> sub_results = lexorderArray(total-i, remainder_pos-1, indices, pos+1);
        
        for (auto& seq : sub_results) {
            all_sequences.push_back(seq);
        }
    }

    return all_sequences;
}