cmake_minimum_required(VERSION 3.22)

project(algs4_cpp)

set(ALGS4_CPP_LIB_SRC
	lib/src/union_find.cpp)
set(CMAKE_BUILD_TYPE "Debug")

add_definitions(-DVISUAL)

include_directories(include)

add_library(algs4 ${ALGS4_CPP_LIB_SRC})

link_directories(${CMAKE_BINARY_DIR})
link_libraries(algs4 mgl)

add_subdirectory(lib/test)
add_subdirectory(lib/visual)
