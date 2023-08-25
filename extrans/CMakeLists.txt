
cmake_minimum_required(VERSION 3.12)
project(extrans_krkrsdl2)

include(FetchContent)

FetchContent_Declare(
	krkrsdl2-tp_stub
	URL https://github.com/krkrsdl2/krkrsdl2/releases/download/latest/krkrsdl2-tp_stub.tar.gz
)

FetchContent_MakeAvailable(krkrsdl2-tp_stub)

set(EXTRANS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(STRINGS ${EXTRANS_SRC_DIR}/src_list/sources.txt EXTRANS_SRC)
file(STRINGS ${EXTRANS_SRC_DIR}/src_list/includes.txt EXTRANS_INCLUDES)
list(TRANSFORM EXTRANS_SRC PREPEND ${EXTRANS_SRC_DIR}/)
list(TRANSFORM EXTRANS_INCLUDES PREPEND ${EXTRANS_SRC_DIR}/)

add_library(extrans MODULE)
set_target_properties(extrans PROPERTIES CXX_STANDARD 11)
set_target_properties(extrans PROPERTIES PREFIX "")
target_sources(extrans PRIVATE ${EXTRANS_SRC})
target_include_directories(extrans PRIVATE ${EXTRANS_INCLUDES})
target_link_libraries(extrans tp_stub)
