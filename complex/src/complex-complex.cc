#include "complex-complex.h"

#include <complex>
#include <iostream>
#include <vector>

#include <benchmark/benchmark.h>

static constexpr int N{20000};

static void StdComplex(benchmark::State& state) {
    std::vector<std::complex<float>> input(N);
    for(unsigned i = 0; i < N; ++i) {
        input[i] = {static_cast<float>(i), static_cast<float>(i + 1)};
    }

    std::vector<std::complex<float>> output(N);

    for(auto _ : state) {
        for(unsigned i = 0; i < N; ++i) {
            output[i] = input[i];
        }
    }
}

static void CustomComplex(benchmark::State& state) {
    std::vector<complex_float> input(N);
    for(unsigned i = 0; i < N; ++i) {
        input[i] = {static_cast<float>(i), static_cast<float>(i + 1)};
    }

    std::vector<complex_float> output(N);

    for(auto _ : state) {
        for(unsigned i = 0; i < N; ++i) {
            output[i] = input[i];
        }
    }
}

BENCHMARK(StdComplex)->Unit(benchmark::kMicrosecond);
BENCHMARK(CustomComplex)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();