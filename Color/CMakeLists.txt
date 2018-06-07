project(Color)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(Color_SOURCE_FILES
        main.cpp)

add_executable(Color ${Color_SOURCE_FILES})

