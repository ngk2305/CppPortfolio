#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

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
    int s = n*n;

    std::vector<double> A(s);
    std::vector<double> B(s);
    std::vector<double> C(s, 0);

    for (int i = 0; i < s; ++i)
            f >> A[i];
    for (int i = 0; i < s; ++i)
            f >> B[i];

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < n; ++i)
        for (int k = 0; k < n; ++k)
            for (int j = 0; j < n; ++j)
                C[i*n+j] += A[i*n+k] * B[k*n+j];

    auto end = std::chrono::steady_clock::now();
    double secs = std::chrono::duration<double>(end - start).count();

 
    std::cout << "elapsed: " << secs << " s\n";
    return 0;
}
