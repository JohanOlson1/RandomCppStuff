add_executable(matrix src/matrix-matrix.cc)

set_target_properties(matrix PROPERTIES COMPILE_FLAGS "-O3 -flto")

target_include_directories(matrix PUBLIC include)

target_link_libraries(matrix  PRIVATE
                               IPP::ippcore IPP::ipps
                               benchmark::benchmark)