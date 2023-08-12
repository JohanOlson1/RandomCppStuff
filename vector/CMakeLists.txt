add_executable(vector src/vector-vector.cc)

set_target_properties(vector PROPERTIES COMPILE_FLAGS "-O3 -flto")

target_include_directories(vector PUBLIC include)

target_link_libraries(vector  PRIVATE
                               IPP::ippcore IPP::ipps
                               benchmark::benchmark)