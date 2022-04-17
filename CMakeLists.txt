cmake_minimum_required(VERSION 3.21)
project(mode_compress)

set(CMAKE_CXX_STANDARD 17 "  -Wall -Wextra")


set(LIBPMEMOBJ_CPP_REQUIRED_VERSION 1.9)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPMEMKV REQUIRED libpmemkv)
pkg_check_modules(LIBPMEMOBJ++ REQUIRED libpmemobj++>=${LIBPMEMOBJ_CPP_REQUIRED_VERSION})

include_directories(${LIBPMEMKV_INCLUDE_DIRS})
link_directories(${LIBPMEMKV_LIBRARY_DIRS})

include_directories(include)

add_executable(mode_compress main.cpp include/tools.h src/tools.cpp include/compress_treenode.h src/compress_treenode.cpp include/compress_tree.h src/compress_tree.cpp include/proper_tree.h src/proper_tree.cpp include/filemeta.h src/filemeta.cpp)

target_link_libraries(mode_compress ${LIBPMEMKV_LIBRARIES} pthread)