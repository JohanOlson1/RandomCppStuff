#include "cfar.h"

#include <array>
#include <iostream>
#include <memory>
#include <vector>

#include <benchmark/benchmark.h>
#include <ipps.h>

static void CFAR(benchmark::State& state) {
    constexpr unsigned N_rows{1000};
    constexpr unsigned N_cols{512};
    constexpr unsigned N_avg{8};
    constexpr unsigned N_guard{5};
    
    std::array<float, N_rows * N_cols> input_data;
    for(unsigned row = 0; row < N_rows; ++row) {
        for(unsigned col = 0; col < N_cols; ++col) {
            input_data[row * N_cols + col] = static_cast<float>(row * col + 1);
        }
    }

    std::array<float, N_rows * N_cols> noise_averages;

    for(auto _ : state) {
        CFAR_1D(input_data.data(), N_rows, N_cols, N_avg, N_guard, noise_averages.data());
    }
}

void CFAR_1D(const float* input,
             const unsigned N_rows,
             const unsigned N_cols,
             const unsigned N_avg,
             const unsigned N_guard,
             float* noise_averages) {
    const unsigned edge_overlap{N_avg + N_guard};
    const unsigned N_tot{N_cols + 2 * edge_overlap - N_avg + 1};
    
    std::vector<float> buffer(N_tot);
    std::fill_n(buffer.begin(), N_tot, 0); // Should already be zero! But good practice
    
    for(unsigned row = 0; row < N_rows; ++row) {
        const float* in{&input[row * N_cols]};
        float* out{&noise_averages[row * N_cols]};

        BasicSlidingWindowSum(in, N_cols, N_avg, N_guard, buffer.data());    
        CalculateEdgeSum(in, N_cols, N_avg, N_guard, buffer.data());
        ippsMaxEvery_32f(buffer.data(), &buffer[edge_overlap + N_guard + 1], out, N_cols);
        ippsDivC_32f_I(static_cast<Ipp32f>(N_avg), out, static_cast<int>(N_cols));
    }
}

void BasicSlidingWindowSum(const float* const in,
                           const unsigned N_in,
                           const unsigned N_avg,
                           const unsigned N_guard,
                           float* const output_buffer) {
    float sum{0};
    unsigned buffer_index{N_guard + 1};
    for(unsigned col = 0; col < N_avg; ++col) {
        sum += in[col];
        output_buffer[buffer_index++] = sum;
    }

    for(unsigned col = N_avg; col < N_in; ++col) {
        sum -= in[col - N_avg];
        sum += in[col];
        output_buffer[buffer_index++] = sum;
    }

    for(unsigned col = 0; col < N_avg; ++col) {
        sum -= in[N_in - N_avg - col];
        output_buffer[buffer_index++] = sum;
    }
}

void CalculateEdgeSum([[maybe_unused]]const float* const in,
                      const unsigned N_in,
                      const unsigned N_avg,
                      const unsigned N_guard,
                      float* const buffer) {
    const unsigned edge_overlap{N_avg + N_guard};
    const unsigned N_tot{N_in + 2 * edge_overlap - N_avg + 1};

    // Direct copy/mirror other side
    for(unsigned i = 0; i < edge_overlap; ++i) {
        const unsigned offset{edge_overlap + N_guard + 1};
        buffer[i] = buffer[offset + i];
        buffer[N_tot - i - 1] = buffer[N_tot - offset - i - 1];
    }

}

BENCHMARK(CFAR)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();