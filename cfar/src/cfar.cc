#include "cfar.h"

#include <array>
#include <iostream>
#include <memory>

#include <benchmark/benchmark.h>

void CFAR_1D(const float* const input, const unsigned N_rows, const unsigned N_cols, float* noise_averages) {
    
}

static void CFAR(benchmark::State& state) {
    constexpr unsigned N_rows{200};
    constexpr unsigned N_cols{1000};
    
    std::array<float, N_rows * N_cols> input_data;
    for(unsigned row = 0; row < N_rows; ++row) {
        for(unsigned col = 0; col < N_cols; ++col) {
            input_data[row * N_cols + col] = row * col;
        }
    }

    std::array<float, N_rows * N_cols> noise_averages;

    for(auto _ : state) {
        CFAR_1D(input_data.data(), N_rows, N_cols, noise_averages.data());
    }
}

BENCHMARK(CFAR);

BENCHMARK_MAIN();