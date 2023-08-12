#include "matrix-matrix.h"

#include <iostream>
#include <vector>

#include <benchmark/benchmark.h>

namespace app {

template<typename T>
T matrix<T>::at(const unsigned row, const unsigned col) const {
    return data_.at(row * cols_ + col);
}

}

static constexpr int N{50000};

static void Test(benchmark::State& state) {

    app::matrix<float> mat(10, 10);

    std::cout << mat.at(2, 2) << "\n";

    for(auto _ : state) {

    }
}
BENCHMARK(Test)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();