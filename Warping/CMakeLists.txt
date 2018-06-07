project(Warping)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(Warping_SOURCE_FILES
        main.cpp)

add_executable(Warping ${Warping_SOURCE_FILES})

