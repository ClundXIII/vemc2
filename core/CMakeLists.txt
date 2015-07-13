
project(libvcore)
cmake_minimum_required(VERSION 2.8)

set(VESPER_INCLUDE_DIR "" CACHE FILEPATH "/usr/include")

#if(NOT "${VESPER_INCLUDE_DIR}/Logging.hpp")
#  message("Can't find Logging.h in ${VESPER_INCLUDE_DIR}")
#endif()

include_directories(${VESPER_INCLUDE_DIR})

# add header files of this module
set(HEADERS
    ${PROJECT_SOURCE_DIR}/field/Efield.h
    ${PROJECT_SOURCE_DIR}/field/Gfield.h
    ${PROJECT_SOURCE_DIR}/field/field.h
    ${PROJECT_SOURCE_DIR}/simulation/effectthread.h
    ${PROJECT_SOURCE_DIR}/simulation/sim_thread.h
    ${PROJECT_SOURCE_DIR}/define.h
    ${PROJECT_SOURCE_DIR}/effect/effect.h
    ${PROJECT_SOURCE_DIR}/effect/inertia.h
    ${PROJECT_SOURCE_DIR}/effect/gravitation.h
    ${PROJECT_SOURCE_DIR}/mymath/math_struct.h
    ${PROJECT_SOURCE_DIR}/mymath/vector.h
    ${PROJECT_SOURCE_DIR}/mymath/vec3bdt.h
    ${PROJECT_SOURCE_DIR}/mymath/eld.h
    ${PROJECT_SOURCE_DIR}/universe.h
    ${PROJECT_SOURCE_DIR}/settings/settings.h
    ${PROJECT_SOURCE_DIR}/settings/settingdefines.h
    ${PROJECT_SOURCE_DIR}/myMath.h
    ${PROJECT_SOURCE_DIR}/object/drawable.h
    ${PROJECT_SOURCE_DIR}/object/noobject.h
    ${PROJECT_SOURCE_DIR}/object/object.h
    ${PROJECT_SOURCE_DIR}/object/quant.h
    ${PROJECT_SOURCE_DIR}/object/body.h
    ${PROJECT_SOURCE_DIR}/simulation.h
)

# add API header files of this module
set(API_HEADERS
    ${PROJECT_SOURCE_DIR}/field/Efield.h
    ${PROJECT_SOURCE_DIR}/field/Gfield.h
    ${PROJECT_SOURCE_DIR}/field/field.h
    ${PROJECT_SOURCE_DIR}/simulation/effectthread.h
    ${PROJECT_SOURCE_DIR}/simulation/sim_thread.h
    ${PROJECT_SOURCE_DIR}/define.h
    ${PROJECT_SOURCE_DIR}/effect/effect.h
    ${PROJECT_SOURCE_DIR}/effect/inertia.h
    ${PROJECT_SOURCE_DIR}/effect/gravitation.h
    ${PROJECT_SOURCE_DIR}/mymath/math_struct.h
    ${PROJECT_SOURCE_DIR}/mymath/vector.h
    ${PROJECT_SOURCE_DIR}/mymath/vec3bdt.h
    ${PROJECT_SOURCE_DIR}/mymath/eld.h
    ${PROJECT_SOURCE_DIR}/universe.h
    ${PROJECT_SOURCE_DIR}/settings/settings.h
    ${PROJECT_SOURCE_DIR}/settings/settingdefines.h
    ${PROJECT_SOURCE_DIR}/myMath.h
    ${PROJECT_SOURCE_DIR}/object/drawable.h
    ${PROJECT_SOURCE_DIR}/object/noobject.h
    ${PROJECT_SOURCE_DIR}/object/object.h
    ${PROJECT_SOURCE_DIR}/object/quant.h
    ${PROJECT_SOURCE_DIR}/object/body.h
    ${PROJECT_SOURCE_DIR}/simulation.h

)

# add source files of this module
set(SOURCES
    ${PROJECT_SOURCE_DIR}/object/object.cpp
    ${PROJECT_SOURCE_DIR}/object/body.cpp
    ${PROJECT_SOURCE_DIR}/mymath/eld.cpp
    ${PROJECT_SOURCE_DIR}/object/noobject.cpp
    ${PROJECT_SOURCE_DIR}/field/field.cpp
    ${PROJECT_SOURCE_DIR}/object/quant.cpp
    ${PROJECT_SOURCE_DIR}/universe.cpp
    ${PROJECT_SOURCE_DIR}/object/drawable.cpp
    ${PROJECT_SOURCE_DIR}/settings/settings.cpp
    ${PROJECT_SOURCE_DIR}/settings/ccs.cpp
    ${PROJECT_SOURCE_DIR}/effect/inertia.cpp
    ${PROJECT_SOURCE_DIR}/effect/effect.cpp
    ${PROJECT_SOURCE_DIR}/field/Gfield.cpp
    ${PROJECT_SOURCE_DIR}/field/Efield.cpp
    ${PROJECT_SOURCE_DIR}/simulation/sim_thread.cpp
    ${PROJECT_SOURCE_DIR}/simulation/effectthread.cpp
    ${PROJECT_SOURCE_DIR}/effect/gravitation.cpp
    ${PROJECT_SOURCE_DIR}/mymath/vector.cpp
    ${PROJECT_SOURCE_DIR}/mymath/vec3bdt.cpp
)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -g -fsanitize=address")
#set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -g")

# add object files to be compiled
add_library(libvcore-objects OBJECT ${HEADERS} ${SOURCES})

# combine object files to static and shared library
add_library(vcore-static STATIC $<TARGET_OBJECTS:libvcore-objects>)
add_library(vcore SHARED $<TARGET_OBJECTS:libvcore-objects>)

install(TARGETS vcore-static ARCHIVE DESTINATION lib)
install(TARGETS vcore LIBRARY DESTINATION lib)

MACRO(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)

FOREACH(HEADER ${${HEADER_LIST}})
STRING(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
INSTALL(FILES ${HEADER} DESTINATION include/${DIR})
ENDFOREACH(HEADER)

ENDMACRO(INSTALL_HEADERS_WITH_DIRECTORY)

#INSTALL_HEADERS_WITH_DIRECTORY(HEADERS)

INSTALL( DIRECTORY ${PROJECT_SOURCE_DIR} DESTINATION /usr/local/include/vemc2/ )
