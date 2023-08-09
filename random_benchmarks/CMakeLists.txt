add_executable(benchmarks src/random_benchmarks-main.cc)

set_target_properties(benchmarks PROPERTIES COMPILE_FLAGS "-O3 -flto")

target_include_directories(benchmarks PUBLIC include)

target_link_libraries(benchmarks  PRIVATE
                                  MKL::MKL
                                  IPP::ippcore IPP::ipps
                                  benchmark::benchmark)