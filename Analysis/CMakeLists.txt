project(Analysis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(Analysis_SOURCE_FILES
        main.cpp)

add_executable(Analysis ${Analysis_SOURCE_FILES})

