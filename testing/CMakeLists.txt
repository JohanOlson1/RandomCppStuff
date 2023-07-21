add_executable(executable src/testing.cc)
target_include_directories(executable PUBLIC include)

add_library(testing_lib)
target_include_directories(testing_lib PUBLIC include)
file(GLOB SOURCE_FILES src/*.cc)
target_sources(testing_lib PUBLIC ${SOURCE_FILES})

target_link_libraries(executable  PRIVATE 
                                  OpenMP::OpenMP_CXX
                                  testing_lib)