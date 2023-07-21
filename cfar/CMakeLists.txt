add_executable(cfar src/cfar.cc)

set_target_properties(cfar PROPERTIES COMPILE_FLAGS "-O3 -flto")

target_include_directories(cfar PUBLIC include)

target_link_libraries(cfar  PRIVATE
                            OpenMP::OpenMP_CXX
                            IPP::ippcore IPP::ipps
                            benchmark::benchmark)