#include "complex-complex.h"

#include <complex>
#include <iostream>
#include <vector>

#include <benchmark/benchmark.h>

namespace app {

}

static constexpr int N{100000};

template<typename T>
class StdComplexF : public benchmark::Fixture {
  public:
    StdComplexF() {
        input1.reserve(N);
        input2.reserve(N);
        for(unsigned i = 0; i < N; ++i) {
            input1[i] = {static_cast<T>(std::rand() % 100), static_cast<T>(std::rand() % 100)};
            input2[i] = {static_cast<T>(std::rand() % 100), static_cast<T>(std::rand() % 100)};
        }
        output.reserve(N);
    }

  protected:
    std::vector<std::complex<T>> input1;
    std::vector<std::complex<T>> input2;
    std::vector<std::complex<T>> output;
};

BENCHMARK_TEMPLATE_DEFINE_F(StdComplexF, Copy, float)(benchmark::State& state) {
    for(auto _ : state) {
        for(unsigned i = 0; i < N; ++i) {
            output[i] = input1[i];
        }
    }
}

BENCHMARK_TEMPLATE_DEFINE_F(StdComplexF, Add, float)(benchmark::State& state) {
    for(auto _ : state) {
        for(unsigned i = 0; i < N; ++i) {
            output[i] = input1[i] + input2[i];
        }
    }
}

BENCHMARK_TEMPLATE_DEFINE_F(StdComplexF, Sub, float)(benchmark::State& state) {
    for(auto _ : state) {
        for(unsigned i = 0; i < N; ++i) {
            output[i] = input1[i] - input2[i];
        }
    }
}

BENCHMARK_TEMPLATE_DEFINE_F(StdComplexF, Div, float)(benchmark::State& state) {
    for(auto _ : state) {
        for(unsigned i = 0; i < N; ++i) {
            output[i] = input1[i] / input2[i];
        }
    }
}

BENCHMARK_TEMPLATE_DEFINE_F(StdComplexF, Mul, float)(benchmark::State& state) {
    for(auto _ : state) {
        for(unsigned i = 0; i < N; ++i) {
            output[i] = input1[i] * input2[i];
        }
    }
}

BENCHMARK_REGISTER_F(StdComplexF, Copy)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(StdComplexF, Add)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(StdComplexF, Sub)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(StdComplexF, Mul)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(StdComplexF, Div)->Unit(benchmark::kMicrosecond);

template<typename T>
class AppComplexF : public benchmark::Fixture {
  public:
    AppComplexF() {
        input1.reserve(N);
        input2.reserve(N);
        for(unsigned i = 0; i < N; ++i) {
            input1[i] = {static_cast<T>(std::rand() % 100), static_cast<T>(std::rand() % 100)};
            input2[i] = {static_cast<T>(std::rand() % 100), static_cast<T>(std::rand() % 100)};
        }
        output.reserve(N);
    }

  protected:
    std::vector<app::complex<T>> input1;
    std::vector<app::complex<T>> input2;
    std::vector<app::complex<T>> output;
};

BENCHMARK_TEMPLATE_DEFINE_F(AppComplexF, Copy, float)(benchmark::State& state) {
    for(auto _ : state) {
        for(unsigned i = 0; i < N; ++i) {
            output[i] = input1[i];
        }
    }
}

BENCHMARK_TEMPLATE_DEFINE_F(AppComplexF, Add, float)(benchmark::State& state) {
    for(auto _ : state) {
        for(unsigned i = 0; i < N; ++i) {
            output[i] = input1[i] + input2[i];
        }
    }
}

BENCHMARK_TEMPLATE_DEFINE_F(AppComplexF, Sub, float)(benchmark::State& state) {
    for(auto _ : state) {
        for(unsigned i = 0; i < N; ++i) {
            output[i] = input1[i] - input2[i];
        }
    }
}

BENCHMARK_TEMPLATE_DEFINE_F(AppComplexF, Mul, float)(benchmark::State& state) {
    for(auto _ : state) {
        for(unsigned i = 0; i < N; ++i) {
            output[i] = input1[i] * input2[i];
        }
    }
}


BENCHMARK_TEMPLATE_DEFINE_F(AppComplexF, Div, float)(benchmark::State& state) {
    for(auto _ : state) {
        for(unsigned i = 0; i < N; ++i) {
            output[i] = input1[i] / input2[i];
        }
    }
}

BENCHMARK_REGISTER_F(AppComplexF, Copy)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(AppComplexF, Add)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(AppComplexF, Sub)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(AppComplexF, Mul)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(AppComplexF, Div)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();