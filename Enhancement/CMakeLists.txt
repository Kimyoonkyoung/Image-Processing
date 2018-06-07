project(Enhancement)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(Enhancement_SOURCE_FILES
        main.cpp)

add_executable(Enhancement ${Enhancement_SOURCE_FILES})

