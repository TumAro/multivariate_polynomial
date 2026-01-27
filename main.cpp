#include "src/utils.h"

int main() {
    auto result = lexorderArray(2, 4);
    
    std::cout << "Generated sequences:" << std::endl;
    for (auto& seq : result) {
        std::cout << "(";
        for (int i = 0; i < seq.size(); i++) {
            std::cout << seq[i];
            if (i < seq.size() - 1) std::cout << ", ";
        }
        std::cout << ")" << std::endl;
    }
    return 0;
}