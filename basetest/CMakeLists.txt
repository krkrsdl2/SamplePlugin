
cmake_minimum_required(VERSION 3.12)
project(basetest_krkrsdl2)

include(FetchContent)

FetchContent_Declare(
	krkrsdl2-tp_stub
	URL https://github.com/krkrsdl2/krkrsdl2/releases/download/latest/krkrsdl2-tp_stub.tar.gz
)

FetchContent_MakeAvailable(krkrsdl2-tp_stub)

set(BASETEST_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(STRINGS ${BASETEST_SRC_DIR}/src_list/sources.txt BASETEST_SRC)
file(STRINGS ${BASETEST_SRC_DIR}/src_list/includes.txt BASETEST_INCLUDES)
list(TRANSFORM BASETEST_SRC PREPEND ${BASETEST_SRC_DIR}/)
list(TRANSFORM BASETEST_INCLUDES PREPEND ${BASETEST_SRC_DIR}/)

add_library(basetest MODULE)
set_target_properties(basetest PROPERTIES CXX_STANDARD 11)
set_target_properties(basetest PROPERTIES PREFIX "")
target_sources(basetest PRIVATE ${BASETEST_SRC})
target_include_directories(basetest PRIVATE ${BASETEST_INCLUDES})
target_link_libraries(basetest tp_stub)
