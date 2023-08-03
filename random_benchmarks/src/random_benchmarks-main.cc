#include "random_benchmarks-main.h"

#include <algorithm>
#include <complex>
#include <cstring>
#include <iostream>
#include <vector>

#include <ipps.h>
#include <benchmark/benchmark.h>

static constexpr unsigned N{800};

static void MemCopy(benchmark::State& state) {
    std::vector<std::complex<float>> input(N);
    std::vector<std::complex<float>> output(N);

    for(auto _ : state) {
        for(unsigned i = 0; i < 1000; ++i) {   
            std::memcpy(output.data(), input.data(), N * sizeof(std::complex<float>));
        }
    }
}

static void IppMove(benchmark::State& state) {
    std::vector<std::complex<float>> input(N);
    std::vector<std::complex<float>> output(N);

    for(auto _ : state) {
        for(unsigned i = 0; i < 1000; ++i) {   
            ippsMove_32fc(reinterpret_cast<Ipp32fc*>(input.data()),
                        reinterpret_cast<Ipp32fc*>(output.data()),
                        N);
        }
    }
}

static void StdCopy(benchmark::State& state) {
    std::vector<std::complex<float>> input(N);
    std::vector<std::complex<float>> output(N);

    for(auto _ : state) {
        for(unsigned i = 0; i < 1000; ++i) {   
            std::copy_n(input.begin(), N, output.begin());
        }
    }
}

BENCHMARK(MemCopy)->Unit(benchmark::kMicrosecond);
BENCHMARK(IppMove)->Unit(benchmark::kMicrosecond);
BENCHMARK(StdCopy)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();