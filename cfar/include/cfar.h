
#ifndef CFAR_CFAR
#define CFAR_CFAR

enum SlidingWindowSumOptions {
  Basic,
  Convolution,
  CrossCorrelation,
};

void CFAR_1D(const float* input,
             const unsigned N_rows,
             const unsigned N_cols,
             const unsigned N_avg,
             const unsigned N_guard,
             SlidingWindowSumOptions option,
             float* noise_averages);

void SlidingWindowSum(const float* const in,
                      const unsigned N_cols,
                      const unsigned N_avg,
                      const unsigned N_guard,
                      SlidingWindowSumOptions option,
                      float* const buffer);

void BasicSlidingWindowSum(const float* const in,
                           const unsigned N_cols,
                           const unsigned N_avg,
                           const unsigned N_guard,
                           float* const output_buffer) noexcept;


void ConvolutionSlidingWindowSum(const float* const in,
                                 const unsigned N_cols,
                                 const unsigned N_avg,
                                 const unsigned N_guard,
                                 float* const output_buffer);

void CrossCorrSlidingWindowSum(const float* const in,
                               const unsigned N_cols,
                               const unsigned N_avg,
                               const unsigned N_guard,
                               float* const output_buffer);

void CalculateEdgeSum(const float* const in,
                      const unsigned N_cols,
                      const unsigned N_avg,
                      const unsigned N_guard,
                      float* const buffer);

#endif // CFAR_CFAR