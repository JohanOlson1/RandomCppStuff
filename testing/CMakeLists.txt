add_executable(executable src/play.cc)

target_include_directories(executable PUBLIC include)

target_link_libraries(executable  PRIVATE 
                                OpenMP::OpenMP_CXX)