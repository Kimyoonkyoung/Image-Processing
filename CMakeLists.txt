cmake_minimum_required(VERSION 3.3)
project(ImageProcessing)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib)

# find OpenCV
find_package( OpenCV REQUIRED )
link_libraries( ${OpenCV_LIBS} )
include_directories( ${OpenCV_INCLUDE_DIRS} )
list( APPEND INCLUDE_DIRECTORIES ${OpenCV_INCLUDE_DIRS} )
list( APPEND LINK_LIBRARIES ${OpenCV_LIBS} )

#add_subdirectory(Analysis)
add_subdirectory(Color)
#add_subdirectory(Enhancement)
#add_subdirectory(ImageFormat)
#add_subdirectory(Warping)