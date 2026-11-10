// common/timer.hpp — tiny header-only timing helpers for benchmarks.
//
// Usage:
//   #include "timer.hpp"
//   Timer t;                     // starts timing on construction
//   do_work();
//   double ms = t.elapsed_ms();
//
//   // Or time a callable several times and get the best run (in ms):
//   double best = time_best_ms([&] { do_work(); }, /*reps=*/10);
#pragma once

#include <algorithm>
#include <chrono>
#include <limits>

class Timer {
public:
    using clock = std::chrono::steady_clock;

    Timer() : start_(clock::now()) {}

    void reset() { start_ = clock::now(); }

    double elapsed_s() const {
        return std::chrono::duration<double>(clock::now() - start_).count();
    }
    double elapsed_ms() const { return elapsed_s() * 1e3; }
    double elapsed_us() const { return elapsed_s() * 1e6; }

private:
    clock::time_point start_;
};

// Runs `f` `reps` times and returns the fastest run in milliseconds.
template <typename F>
double time_best_ms(F&& f, int reps = 5) {
    double best = std::numeric_limits<double>::infinity();
    for (int i = 0; i < reps; ++i) {
        Timer t;
        f();
        best = std::min(best, t.elapsed_ms());
    }
    return best;
}
