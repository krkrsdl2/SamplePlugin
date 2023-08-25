
cmake_minimum_required(VERSION 3.12)
project(nativeclasstest_krkrsdl2)

include(FetchContent)

FetchContent_Declare(
	krkrsdl2-tp_stub
	URL https://github.com/krkrsdl2/krkrsdl2/releases/download/latest/krkrsdl2-tp_stub.tar.gz
)

FetchContent_MakeAvailable(krkrsdl2-tp_stub)

set(NATIVECLASSTEST_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(STRINGS ${NATIVECLASSTEST_SRC_DIR}/src_list/sources.txt NATIVECLASSTEST_SRC)
file(STRINGS ${NATIVECLASSTEST_SRC_DIR}/src_list/includes.txt NATIVECLASSTEST_INCLUDES)
list(TRANSFORM NATIVECLASSTEST_SRC PREPEND ${NATIVECLASSTEST_SRC_DIR}/)
list(TRANSFORM NATIVECLASSTEST_INCLUDES PREPEND ${NATIVECLASSTEST_SRC_DIR}/)

add_library(nativeclasstest MODULE)
set_target_properties(nativeclasstest PROPERTIES CXX_STANDARD 11)
set_target_properties(nativeclasstest PROPERTIES PREFIX "")
target_sources(nativeclasstest PRIVATE ${NATIVECLASSTEST_SRC})
target_include_directories(nativeclasstest PRIVATE ${NATIVECLASSTEST_INCLUDES})
target_link_libraries(nativeclasstest tp_stub)
