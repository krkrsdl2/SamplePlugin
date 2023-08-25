
cmake_minimum_required(VERSION 3.12)
project(xp3dec_krkrsdl2)

include(FetchContent)

FetchContent_Declare(
	krkrsdl2-tp_stub
	URL https://github.com/krkrsdl2/krkrsdl2/releases/download/latest/krkrsdl2-tp_stub.tar.gz
)

FetchContent_MakeAvailable(krkrsdl2-tp_stub)

set(XP3DEC_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(STRINGS ${XP3DEC_SRC_DIR}/src_list/sources.txt XP3DEC_SRC)
file(STRINGS ${XP3DEC_SRC_DIR}/src_list/includes.txt XP3DEC_INCLUDES)
list(TRANSFORM XP3DEC_SRC PREPEND ${XP3DEC_SRC_DIR}/)
list(TRANSFORM XP3DEC_INCLUDES PREPEND ${XP3DEC_SRC_DIR}/)

add_library(xp3dec MODULE)
set_target_properties(xp3dec PROPERTIES CXX_STANDARD 11)
set_target_properties(xp3dec PROPERTIES PREFIX "")
target_sources(xp3dec PRIVATE ${XP3DEC_SRC})
target_include_directories(xp3dec PRIVATE ${XP3DEC_INCLUDES})
target_link_libraries(xp3dec tp_stub)
