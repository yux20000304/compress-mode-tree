cmake_minimum_required(VERSION 3.21)
project(mode_compress)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(mode_compress main.cpp include/tools.h src/tools.cpp include/compress_treenode.h src/compress_treenode.cpp include/compress_tree.h src/compress_tree.cpp)
