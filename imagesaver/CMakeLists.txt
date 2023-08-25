
cmake_minimum_required(VERSION 3.12)
project(imagesaver_krkrsdl2)

include(FetchContent)

FetchContent_Declare(
	krkrsdl2-tp_stub
	URL https://github.com/krkrsdl2/krkrsdl2/releases/download/latest/krkrsdl2-tp_stub.tar.gz
)

FetchContent_MakeAvailable(krkrsdl2-tp_stub)

set(IMAGESAVER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(STRINGS ${IMAGESAVER_SRC_DIR}/src_list/sources.txt IMAGESAVER_SRC)
file(STRINGS ${IMAGESAVER_SRC_DIR}/src_list/includes.txt IMAGESAVER_INCLUDES)
list(TRANSFORM IMAGESAVER_SRC PREPEND ${IMAGESAVER_SRC_DIR}/)
list(TRANSFORM IMAGESAVER_INCLUDES PREPEND ${IMAGESAVER_SRC_DIR}/)

add_library(imagesaver MODULE)
set_target_properties(imagesaver PROPERTIES CXX_STANDARD 11)
set_target_properties(imagesaver PROPERTIES PREFIX "")
target_sources(imagesaver PRIVATE ${IMAGESAVER_SRC})
target_include_directories(imagesaver PRIVATE ${IMAGESAVER_INCLUDES})
target_link_libraries(imagesaver tp_stub)
