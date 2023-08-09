#include "random_benchmarks-main.h"

#include <algorithm>
#include <complex>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include <benchmark/benchmark.h>
#include <ipps.h>
#include <mkl.h>

static constexpr unsigned N{10000};    

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

BENCHMARK_DEFINE_F(CopyF, IppsMove)(benchmark::State& state) {
    for(auto _ : state) {
        ippsMove_32fc(reinterpret_cast<Ipp32fc*>(input.data()),
                      reinterpret_cast<Ipp32fc*>(output.data()),
                      N);
    }
}

BENCHMARK_DEFINE_F(CopyF, IppsCopy)(benchmark::State& state) {
    for(auto _ : state) {
        ippsCopy_32fc(reinterpret_cast<Ipp32fc*>(input.data()),
                      reinterpret_cast<Ipp32fc*>(output.data()),
                      N);
    }
}

BENCHMARK_DEFINE_F(CopyF, StdCopy)(benchmark::State& state) {
    for(auto _ : state) {
        std::copy_n(input.begin(), N, output.begin());
    }
}

BENCHMARK_DEFINE_F(CopyF, MklCopy)(benchmark::State& state) {
    for(auto _ : state) {
        cblas_ccopy(N, reinterpret_cast<MKL_Complex8*>(input.data()), 1, reinterpret_cast<MKL_Complex8*>(output.data()), 1);
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

BENCHMARK_REGISTER_F(CopyF, Memcpy)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(CopyF, IppsMove)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(CopyF, IppsCopy)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(CopyF, StdCopy)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(CopyF, MklCopy)->Unit(benchmark::kMicrosecond);;

BENCHMARK_REGISTER_F(ZeroInitializeF, StdFill)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(ZeroInitializeF, IppsZero)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(ZeroInitializeF, VectorAssign)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();