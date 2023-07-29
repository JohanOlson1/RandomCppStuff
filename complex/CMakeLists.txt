add_executable(complex src/complex-complex.cc)

set_target_properties(complex PROPERTIES COMPILE_FLAGS "-O3 -flto")

target_include_directories(complex PUBLIC include)

target_link_libraries(complex  PRIVATE
                               IPP::ippcore IPP::ipps
                               benchmark::benchmark)