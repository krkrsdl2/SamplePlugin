
cmake_minimum_required(VERSION 3.12)
project(extrans_krkrsdl2)

set(PLUGIN_NAME extrans)
set(PLUGIN_DEPS tp_stub)

if((NOT DEFINED CMAKE_BUILD_TYPE) OR (NOT CMAKE_BUILD_TYPE) OR (CMAKE_BUILD_TYPE STREQUAL ""))
if(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
set(CMAKE_BUILD_TYPE MinSizeRel)
else()
set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()
endif()

set(PLUGIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(STRINGS ${PLUGIN_SRC_DIR}/src_list/sources.txt PLUGIN_SRC)
file(STRINGS ${PLUGIN_SRC_DIR}/src_list/includes.txt PLUGIN_INCLUDES)
list(TRANSFORM PLUGIN_SRC PREPEND ${PLUGIN_SRC_DIR}/)
list(TRANSFORM PLUGIN_INCLUDES PREPEND ${PLUGIN_SRC_DIR}/)

include(FetchContent)

FetchContent_Declare(
	krkrsdl2-tp_stub
	URL https://github.com/krkrsdl2/krkrsdl2/releases/download/latest/krkrsdl2-tp_stub.tar.gz
)

FetchContent_MakeAvailable(krkrsdl2-tp_stub)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
add_executable(${PLUGIN_NAME})
set_target_properties(${PLUGIN_NAME} PROPERTIES SUFFIX ".so")
else()
add_library(${PLUGIN_NAME} MODULE)
endif()
set_target_properties(${PLUGIN_NAME} PROPERTIES CXX_STANDARD 11)
set_target_properties(${PLUGIN_NAME} PROPERTIES PREFIX "")
target_sources(${PLUGIN_NAME} PRIVATE ${PLUGIN_SRC})
target_include_directories(${PLUGIN_NAME} PRIVATE ${PLUGIN_INCLUDES})
target_link_libraries(${PLUGIN_NAME} ${PLUGIN_DEPS})
if(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
target_link_options(${PLUGIN_NAME} PRIVATE
	-sDISABLE_EXCEPTION_CATCHING=0
	-fPIC
	-sSIDE_MODULE=1
)
target_compile_options(${PLUGIN_NAME} PRIVATE
	-sDISABLE_EXCEPTION_CATCHING=0
	-fPIC
)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
target_link_options(${PLUGIN_NAME} PRIVATE
	-O3
)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
target_link_options(${PLUGIN_NAME} PRIVATE
	-O2
)
endif()
if(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
target_link_options(${PLUGIN_NAME} PRIVATE
	-Os
)
endif()
endif()
