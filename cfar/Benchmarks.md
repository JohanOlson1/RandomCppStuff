# Benchmarks

## Hardware

- 8 CPUs @ 2.496 GHz
- 4 cores with 2 CPUs each
- L1 Data: 32 KiB
- L1 Instruction: 32 KiB
- L2: 256 KiB
- L3: 8192 KiB

## Setup

- N_avg = 8
- N_guard = 5
- N_rows = 1000
- N_cols = 512

## BasicSlidingWindowSum

- 1 thread -> 1100 microseconds
- 2 threads -> 560 microseconds
- 3 threads -> 370 microseconds
- 4 threads -> 280 microseconds
- 5 threads -> 230 microseconds
- 6 threads -> 190 microseconds
- 7 threads -> 170 microseconds*
- 8 threads -> 190 microseconds

## CrossCorrSlidingWindowSum
- 1 thread -> 350 microseconds
- 2 threads -> 190 microseconds
- 3 threads -> 140 microseconds
- 4 threads -> 110 microseconds
- 5 threads -> 100 microseconds
- 6 threads -> 97 microseconds
- 7 threads -> 91 microseconds*
- 8 threads -> 110 microseconds
