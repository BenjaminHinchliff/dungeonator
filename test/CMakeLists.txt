cmake_minimum_required(VERSION 3.11)

find_package(Catch2)

if(NOT ${Catch2_FOUND})
include(FetchContent)

FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v2.13.1)

FetchContent_MakeAvailable(Catch2)
endif()

add_executable(tests "main.cpp" "dungeonator_test.cpp")
target_link_libraries(tests PUBLIC Catch2::Catch2)
target_link_libraries(tests PUBLIC dungeonator)

include(CTest)
include(Catch)
catch_discover_tests(tests)
