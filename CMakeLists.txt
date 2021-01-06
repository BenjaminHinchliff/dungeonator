cmake_minimum_required(VERSION 3.11)

project("dungeonator")

option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build doxygen docs" ON)

add_subdirectory("src")
if(BUILD_TESTS)
	add_subdirectory("tests")
endif()
if(BUILD_DOCS)
	add_subdirectory("docs")
endif()
