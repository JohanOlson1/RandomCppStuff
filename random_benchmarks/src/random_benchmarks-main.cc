#include "random_benchmarks-main.h"

#include <algorithm>
#include <complex>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include <ipps.h>
#include <benchmark/benchmark.h>

static constexpr unsigned N{1000};    

class CopyF : public benchmark::Fixture {
  public:
    CopyF() {
        input.reserve(N);
        output.reserve(N);
        for(unsigned i = 0; i < N; ++i) {
            input[i] = {static_cast<float>(std::rand() % 100), static_cast<float>(std::rand() % 100)};
        }
    }

  protected:
    std::vector<std::complex<float>> input;
    std::vector<std::complex<float>> output;
};

BENCHMARK_DEFINE_F(CopyF, Memcpy)(benchmark::State& state) {
    for(auto _ : state) {
        std::memcpy(output.data(), input.data(), N * sizeof(std::complex<float>));
    }
}

BENCHMARK_DEFINE_F(CopyF, IppsCopy)(benchmark::State& state) {
    for(auto _ : state) {
        ippsMove_32fc(reinterpret_cast<Ipp32fc*>(input.data()),
                      reinterpret_cast<Ipp32fc*>(output.data()),
                      N);
    }
}

BENCHMARK_DEFINE_F(CopyF, StdCopy)(benchmark::State& state) {
    for(auto _ : state) {
        std::copy_n(input.begin(), N, output.begin());
    }
}

class ZeroInitializeF : public benchmark::Fixture {
  public:
    ZeroInitializeF() {
        data.reserve(N);
        for(unsigned i = 0; i < N; ++i) {
            data[i] = {static_cast<float>(std::rand() % 100), static_cast<float>(std::rand() % 100)};
        }
    }

  protected:
    std::vector<std::complex<float>> data;
};

BENCHMARK_DEFINE_F(ZeroInitializeF, StdFill)(benchmark::State& state) {
    for(auto _ : state) {
        std::fill_n(data.data(), N, 0.0f);
    }
}

BENCHMARK_DEFINE_F(ZeroInitializeF, IppsZero)(benchmark::State& state) {
    for(auto _ : state) {
        ippsZero_32fc(reinterpret_cast<Ipp32fc*>(data.data()), N);
    }
}

BENCHMARK_DEFINE_F(ZeroInitializeF, VectorAssign)(benchmark::State& state) {
    for(auto _ : state) {
        data.assign(N, {0.0f, 0.0f});
    }
}

BENCHMARK_REGISTER_F(CopyF, Memcpy);
BENCHMARK_REGISTER_F(CopyF, IppsCopy);
BENCHMARK_REGISTER_F(CopyF, StdCopy);

BENCHMARK_REGISTER_F(ZeroInitializeF, StdFill);
BENCHMARK_REGISTER_F(ZeroInitializeF, IppsZero);
BENCHMARK_REGISTER_F(ZeroInitializeF, VectorAssign);

BENCHMARK_MAIN();