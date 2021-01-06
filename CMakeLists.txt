cmake_minimum_required(VERSION 3.8)

project("dungeonator")

option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build doxygen docs" ON)

add_subdirectory("src")
add_subdirectory("tests")
