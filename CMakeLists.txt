
cmake_minimum_required(VERSION 3.12)
project(SamplePlugin_krkrsdl2)

add_subdirectory(basetest)
add_subdirectory(exceptiontest)
add_subdirectory(extrans)
add_subdirectory(imagesaver)
add_subdirectory(nativeclasstest)
add_subdirectory(xp3filter/xp3dec)

set_target_properties(basetest exceptiontest extrans imagesaver nativeclasstest xp3dec
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
