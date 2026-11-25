// bench_matmul.cpp: times matmul_ijk and matmul_ikj with kbench and appends the
// results to phase0/week1/results/kbench.csv. Run from the repo root.
#include "matrix.hpp"
#include "kbench.hpp"
#include <iostream>
#include <string>

int main() {
    const std::string csv = "phase0/week1/results/kbench.csv";
    double sink = 0;   // keeps every matmul result "used" so -O2 can't drop or reshape the work

    for (int size : {512, 1024}) {
        std::string path = "phase0/week1/data/big_" + std::to_string(size) + ".txt";
        std::ifstream f(path);
        if (!f) {
            std::cerr << "cannot open " << path << "\n";
            return 1;
        }
        int n; f >> n;
        auto A = load_matrix<double>(f, n, n);
        auto B = load_matrix<double>(f, n, n);
        std::string suffix = " n=" + std::to_string(n);

        Result results[] = {
            bench("ijk" + suffix, [&] { auto C = matmul_ijk(A, B); sink += C(0,0); }, 2, 10),
            bench("ikj" + suffix, [&] { auto C = matmul_ikj(A, B); sink += C(0,0); }, 2, 10),
        };

        for (const Result& r : results) {
            std::cout << r.loop_type_and_size
                      << "  median: " << r.median_time << " s"
                      << "  min: " << r.min_time << " s\n";
            write_csv(r, csv);
        }
    }

    std::cout << "(sink: " << sink << ")\n";
    std::cout << "appended results to " << csv << "\n";
    return 0;
}
