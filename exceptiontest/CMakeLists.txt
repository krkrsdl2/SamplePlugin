
cmake_minimum_required(VERSION 3.12)
project(exceptiontest_krkrsdl2)

include(FetchContent)

FetchContent_Declare(
	krkrsdl2-tp_stub
	URL https://github.com/krkrsdl2/krkrsdl2/releases/download/latest/krkrsdl2-tp_stub.tar.gz
)

FetchContent_MakeAvailable(krkrsdl2-tp_stub)

set(EXCEPTIONTEST_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(STRINGS ${EXCEPTIONTEST_SRC_DIR}/src_list/sources.txt EXCEPTIONTEST_SRC)
file(STRINGS ${EXCEPTIONTEST_SRC_DIR}/src_list/includes.txt EXCEPTIONTEST_INCLUDES)
list(TRANSFORM EXCEPTIONTEST_SRC PREPEND ${EXCEPTIONTEST_SRC_DIR}/)
list(TRANSFORM EXCEPTIONTEST_INCLUDES PREPEND ${EXCEPTIONTEST_SRC_DIR}/)

add_library(exceptiontest MODULE)
set_target_properties(exceptiontest PROPERTIES CXX_STANDARD 11)
set_target_properties(exceptiontest PROPERTIES PREFIX "")
target_sources(exceptiontest PRIVATE ${EXCEPTIONTEST_SRC})
target_include_directories(exceptiontest PRIVATE ${EXCEPTIONTEST_INCLUDES})
target_link_libraries(exceptiontest tp_stub)
