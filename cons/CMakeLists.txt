
project(vemc2_cons)
cmake_minimum_required(VERSION 2.8)

# add header files of this module
set(HEADERS
    ${PROJECT_SOURCE_DIR}/includesfm.h
)

# add source files of this module
set(SOURCES
    ${PROJECT_SOURCE_DIR}/main.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")

add_executable(vcons ${HEADERS} ${SOURCES})

target_link_libraries(vcons vcore vesper-log)
