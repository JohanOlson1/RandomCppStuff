add_executable(executable src/play.cc)
target_include_directories(executable PUBLIC include)

add_library(play_lib)
target_include_directories(play_lib PUBLIC include)
file(GLOB SOURCE_FILES src/*.cc)
target_sources(play_lib PUBLIC ${SOURCE_FILES})

target_link_libraries(executable  PRIVATE 
                                  OpenMP::OpenMP_CXX
                                  play_lib)