
cmake_minimum_required(VERSION 3.12)
project(wutcwf_krkrsdl2)

include(FetchContent)

FetchContent_Declare(
	krkrsdl2-tp_stub
	URL https://github.com/krkrsdl2/krkrsdl2/releases/download/latest/krkrsdl2-tp_stub.tar.gz
)

FetchContent_MakeAvailable(krkrsdl2-tp_stub)

set(WUTCWF_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(STRINGS ${WUTCWF_SRC_DIR}/src_list/sources.txt WUTCWF_SRC)
file(STRINGS ${WUTCWF_SRC_DIR}/src_list/includes.txt WUTCWF_INCLUDES)
list(TRANSFORM WUTCWF_SRC PREPEND ${WUTCWF_SRC_DIR}/)
list(TRANSFORM WUTCWF_INCLUDES PREPEND ${WUTCWF_SRC_DIR}/)

add_library(wutcwf MODULE)
set_target_properties(wutcwf PROPERTIES CXX_STANDARD 11)
set_target_properties(wutcwf PROPERTIES PREFIX "")
target_sources(wutcwf PRIVATE ${WUTCWF_SRC})
target_include_directories(wutcwf PRIVATE ${WUTCWF_INCLUDES})
target_link_libraries(wutcwf tp_stub)
