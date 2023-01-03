cmake_minimum_required(VERSION 3.21)
project(mode_compress)

set(CMAKE_CXX_STANDARD 17 "  -Wall -Wextra")

set(USE_PMEMKV OFF)

set(SRC_FILES
        include/tools.h
        src/tools.cpp
        include/compress_treenode.h
        src/compress_treenode.cpp
        include/compress_tree.h
        src/compress_tree.cpp
        include/proper_tree.h
        src/proper_tree.cpp
        include/filemeta.h
        src/filemeta.cpp
        )

if(USE_PMEMKV)
    add_definitions(-DUSE_PMEMKV)
endif(USE_PMEMKV)

IF(USE_PMEMKV)

    set(LIBPMEMOBJ_CPP_REQUIRED_VERSION 1.9)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(LIBPMEMKV REQUIRED libpmemkv)
    pkg_check_modules(LIBPMEMOBJ++ REQUIRED libpmemobj++>=${LIBPMEMOBJ_CPP_REQUIRED_VERSION})

    include_directories(${LIBPMEMKV_INCLUDE_DIRS})
    link_directories(${LIBPMEMKV_LIBRARY_DIRS})
ENDIF()

include_directories(include src)

add_executable(mode_compress main.cpp ${SRC_FILES})

IF(USE_PMEMKV)
    target_link_libraries(mode_compress ${LIBPMEMKV_LIBRARIES} pthread)
ELSE()
    target_link_libraries(mode_compress pthread)
ENDIF()