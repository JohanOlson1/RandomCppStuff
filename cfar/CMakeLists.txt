add_executable(cfar src/cfar.cc)

target_include_directories(cfar PUBLIC include)

target_link_libraries(cfar  PRIVATE 
                            OpenMP::OpenMP_CXX
                            benchmark::benchmark)