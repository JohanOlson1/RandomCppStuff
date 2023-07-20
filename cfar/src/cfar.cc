#include "cfar.h"

#include <iostream>
#include <memory>
#include <vector>

#include <benchmark/benchmark.h>
#include <ipps.h>
#include <omp.h>

static void CFAR(benchmark::State& state) {
    constexpr unsigned N_rows{1000};
    constexpr unsigned N_cols{512};
    constexpr unsigned N_avg{8};
    constexpr unsigned N_guard{5};
    
    std::vector<float> input_data(N_rows * N_cols);
    float count{0};
    for(unsigned row = 0; row < N_rows; ++row) {
        for(unsigned col = 0; col < N_cols; ++col) {
            input_data[row * N_cols + col] = count++;
        }
    }

    std::vector<float> noise_averages(N_rows * N_cols);
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
    const unsigned N_buffer{N_cols + 2 * edge_overlap - N_avg + 1};

    const int max_threads{omp_get_max_threads()};
    #pragma omp parallel num_threads(8) \
    default(none) \
    shared(N_rows, N_cols, N_avg, N_guard, edge_overlap, N_buffer, noise_averages, input)
    {
    std::vector<float> buffer(N_buffer);
    std::fill_n(buffer.begin(), N_buffer, 0); // Should already be zero! But good practice
    
    #pragma omp for schedule(dynamic, 8)
    for(unsigned row = 0; row < N_rows; ++row) {
        const float* in{&input[row * N_cols]};
        float* out{&noise_averages[row * N_cols]};

        // CrossCorrSlidingWindowSum(in, N_cols, N_avg, N_guard, buffer.data());
        // ConvolutionSlidingWindowSum(in, N_cols, N_avg, N_guard, buffer.data());
        BasicSlidingWindowSum(in, N_cols, N_avg, N_guard, buffer.data());    
        CalculateEdgeSum(in, N_cols, N_avg, N_guard, buffer.data());
        ippsMaxEvery_32f(buffer.data(), &buffer[edge_overlap + N_guard + 1], out, N_cols);
        ippsDivC_32f_I(static_cast<Ipp32f>(N_avg), out, static_cast<int>(N_cols));
    }
    }
}

void BasicSlidingWindowSum(const float* const in,
                           const unsigned N_cols,
                           const unsigned N_avg,
                           const unsigned N_guard,
                           float* const output_buffer) noexcept {
    float sum{0};
    const unsigned edge_overlap{N_avg + N_guard};
    const unsigned N_buffer{N_cols + 2 * edge_overlap - N_avg + 1};

    unsigned col{0};
    while(col < N_avg) {
        sum += in[col]; // Load up so we can start
        ++col;
    }

    unsigned buffer_index{edge_overlap};
    while(buffer_index < N_buffer - edge_overlap - 1) {
        output_buffer[buffer_index] = sum;
        sum -= in[col - N_avg];
        sum += in[col];

        ++col;
        ++buffer_index;
    }
}

void ConvolutionSlidingWindowSum(const float* const in,
                                 const unsigned N_cols,
                                 const unsigned N_avg,
                                 const unsigned N_guard,
                                 float* const output_buffer) {
    static const std::vector<float> window(N_avg, 1.0f); // Static to avoid reinitialization each call

    IppEnum funCfg{(IppEnum)(ippAlgAuto)};
    int bufSize{0};
    ippsConvolveGetBufferSize(static_cast<int>(N_cols), static_cast<int>(N_avg), ipp32f, funCfg, &bufSize);
    Ipp8u* pBuffer = ippsMalloc_8u(bufSize);

    ippsConvolve_32f(in, static_cast<int>(N_cols),
                     window.data(), static_cast<int>(N_avg),
                     &output_buffer[N_guard + 1], funCfg, pBuffer);

   ippsFree(pBuffer);
}

void CrossCorrSlidingWindowSum(const float* const in,
                               const unsigned N_cols,
                               const unsigned N_avg,
                               const unsigned N_guard,
                               float* const output_buffer) {
    const unsigned edge_overlap{N_avg + N_guard};
    static const std::vector<float> window(N_avg, 1.0f); // Static to avoid reinitialization each call

    const unsigned N_out{N_cols - edge_overlap};
    ippsCrossCorrNorm_32f(window.data(), static_cast<int>(N_avg), 
                          in, static_cast<int>(N_cols),
                          &output_buffer[edge_overlap], static_cast<int>(N_out),
                          0, ippsNormNone, nullptr);
}

void CalculateEdgeSum([[maybe_unused]]const float* const in,
                      const unsigned N_cols,
                      const unsigned N_avg,
                      const unsigned N_guard,
                      float* const buffer) {
    const unsigned edge_overlap{N_avg + N_guard};
    const unsigned N_buffer{N_cols + 2 * edge_overlap - N_avg + 1};

    // Direct copy/mirror other side
    for(unsigned i = 0; i < edge_overlap; ++i) {
        const unsigned offset{edge_overlap + N_guard + 1};
        buffer[i] = buffer[offset + i];
        buffer[N_buffer - i - 1] = buffer[N_buffer - offset - i - 1];
    }
}

BENCHMARK(CFAR)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();