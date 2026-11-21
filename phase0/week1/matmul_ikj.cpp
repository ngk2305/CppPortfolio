#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
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


    auto start = std::chrono::steady_clock::now();

    Matrix<double> C = matmul_ikj<double>(A,B);

    auto end = std::chrono::steady_clock::now();
    double secs = std::chrono::duration<double>(end - start).count();

    if (n <= 5) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) std::cout << C(i,j)  << " ";
            std::cout << "\n";
        }
    }
    std::cout << "elapsed: " << secs << " s\n";
    return 0;
}
