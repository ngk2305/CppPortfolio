#include <vector>
#include <iostream>
#include "matrix.hpp"


int main(int argc, char** argv){
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " <input file>\n";
        return 1;
    }
    std::ifstream f(argv[1]);
    if (!f) {
        std::cerr << "cannot open " << argv[1] << "\n";
        return 1;
    }

    int n; f >> n;

    Matrix<double> A = load_matrix<double>(f, n, n);
    Matrix<double> B = load_matrix<double>(f, n, n);
    
    for (int i = 0; i<n; ++i){
        std::cout << B(0,i);

    }
    return 0;
}