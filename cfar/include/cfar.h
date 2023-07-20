
#ifndef CFAR_CFAR
#define CFAR_CFAR

void CFAR_1D(const float* input,
             const unsigned N_rows,
             const unsigned N_cols,
             const unsigned N_avg,
             const unsigned N_guard,
             float* noise_averages);

void BasicSlidingWindowSum(const float* const in,
                           const unsigned N_cols,
                           const unsigned N_avg,
                           const unsigned N_guard,
                           float* const output_buffer);

void CalculateEdgeSum(const float* const in,
                      const unsigned N_cols,
                      const unsigned N_avg,
                      const unsigned N_guard,
                      float* const buffer);

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

#endif // CFAR_CFAR