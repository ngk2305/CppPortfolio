#pragma once
#include "timer.hpp"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

struct Result {
    double median_time;
    double min_time;
    std::string loop_type_and_size;
    int warmup;
    int reps;
};



template <typename F>
Result bench(const std::string& loop_and_size, F f, int warmup, int reps){
    assert(reps > 0);
    std::vector<double> times(reps);
    /*warmup runs*/
    for (int i = 0; i < warmup; ++i) {
        f();
    }

    for (int i = 0; i < reps; ++i) {
        Timer t;
        f();
        times[i] = t.elapsed_s();
    }
    std::sort(times.begin(), times.end());
    double median;
    if (reps%2 == 0){
        median = (times[reps/2]+times[reps/2-1])/2;
    }
    else {
        median = times[(reps-1)/2];
    }
    Result R{median, times[0], loop_and_size, warmup, reps};
    return R;

}

// Appends one row to a CSV file, writing the header first if the file is new or empty.
inline void write_csv(const Result& r, const std::string& path) {
    bool needs_header;
    {
        std::ifstream check(path);
        needs_header = !check || check.peek() == std::ifstream::traits_type::eof();
    }
    std::ofstream out(path, std::ios::app);
    if (needs_header) {
        out << "name,warmup,reps,median_s,min_s\n";
    }
    out << r.loop_type_and_size << ',' << r.warmup << ',' << r.reps << ','
        << r.median_time << ',' << r.min_time << '\n';
}
