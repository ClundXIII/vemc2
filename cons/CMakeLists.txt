
project(vemc2_cons)
cmake_minimum_required(VERSION 2.8)

set(VEMC_INCLUDE_DIR "" CACHE FILEPATH "/usr/include")
include_directories(${VEMC_INCLUDE_DIR})
include_directories(../core)
link_directories(../core)

set(VESPER_INCLUDE_DIR "" CACHE FILEPATH "/usr/include")
include_directories(${VESPER_INCLUDE_DIR})

set(VESPER_LIB_DIR "" CACHE FILEPATH "/usr/lib")
link_directories(${VESPER_LIB_DIR})

# add header files of this module
set(HEADERS
    ${PROJECT_SOURCE_DIR}/includesfm.h
)

# add source files of this module
set(SOURCES
    ${PROJECT_SOURCE_DIR}/main.cpp
)

SET(GCC_COVERAGE_LINK_FLAGS    "-pthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS} -fsanitize=address -g")
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
add_executable(vcons ${HEADERS} ${SOURCES})

target_link_libraries(vcons vcore vesper-log)
