add_executable(design_patterns src/design_patterns-design_patterns.cc)

set_target_properties(design_patterns PROPERTIES COMPILE_FLAGS "-O3 -flto")

target_include_directories(design_patterns PUBLIC include)

target_link_libraries(design_patterns  PRIVATE
                                       IPP::ippcore IPP::ipps
                                       benchmark::benchmark)