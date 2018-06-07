project(ImageFormat)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(ImageFormat_SOURCE_FILES
        main.cpp)

add_executable(ImageFormat ${ImageFormat_SOURCE_FILES})

