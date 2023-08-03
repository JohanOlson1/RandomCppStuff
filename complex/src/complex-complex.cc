#include "complex-complex.h"

#include <complex>
#include <iostream>
#include <vector>

#include <benchmark/benchmark.h>

enum ComplexOption {
    Copy,
    Add,
    Sub,
    Mul,
};

static constexpr int N{50000};

template<typename T>
static void ComplexOperation(const ComplexOption option,
                             const T* input1,
                             const T* input2,
                             T* output) {
    switch(option) {
        case Copy: {
            for(unsigned i = 0; i < N; ++i) {
                output[i] = input1[i];
            }
            break;
        }
        case Add: {
            for(unsigned i = 0; i < N; ++i) {
                output[i] = input1[i] + input2[i];
            }
            break;
        }
        case Sub: {
            for(unsigned i = 0; i < N; ++i) {
                output[i] = input1[i] - input2[i];
            }
            break;
        }
        case Mul: {
            for(unsigned i = 0; i < N; ++i) {
                output[i] = input1[i] * input2[i];
            }
            break;
        }
        default: {
            std::cout << "Option not implemented\n"; 
        }
    }
}

static void StdComplex(benchmark::State& state) {
    std::vector<std::complex<float>> input1(N);
    std::vector<std::complex<float>> input2(N);
    for(unsigned i = 0; i < N; ++i) {
        input1[i] = {static_cast<float>(i), static_cast<float>(i + 1)};
        input2[i] = {static_cast<float>(i), static_cast<float>(i + 2)};
    }

    std::vector<std::complex<float>> output(N);

    ComplexOption option{static_cast<ComplexOption>(state.range(0))};
    for(auto _ : state) {
        ComplexOperation(option, input1.data(), input2.data(), output.data());
    }
}

static void SipComplex(benchmark::State& state) {
    std::vector<sip::complex<float>> input1(N);
    std::vector<sip::complex<float>> input2(N);
    for(unsigned i = 0; i < N; ++i) {
        input1[i] = {static_cast<float>(i), static_cast<float>(i + 1)};
        input2[i] = {static_cast<float>(i), static_cast<float>(i + 2)};
    }
    std::vector<sip::complex<float>> output(N);

    ComplexOption option{static_cast<ComplexOption>(state.range(0))};
    for(auto _ : state) {
        ComplexOperation(option, input1.data(), input2.data(), output.data());
    }
}

BENCHMARK(StdComplex)->Arg(Copy)->Arg(Add)->Arg(Sub)->Arg(Mul)->Unit(benchmark::kMicrosecond);
BENCHMARK(SipComplex)->Arg(Copy)->Arg(Add)->Arg(Sub)->Arg(Mul)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();