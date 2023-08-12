#include "matrix-matrix.h"

#include <iostream>
#include <vector>

#include <benchmark/benchmark.h>

static constexpr int N{50000};

static void Test(benchmark::State& state) {
    for(auto _ : state) {

    }
}
BENCHMARK(Test)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();