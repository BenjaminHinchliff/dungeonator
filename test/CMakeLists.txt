cmake_minimum_required(VERSION 3.11)

find_package(Catch2 QUIET)
if(NOT ${Catch2_FOUND})
	include(FetchContent)

	FetchContent_Declare(
		catch2
		GIT_REPOSITORY https://github.com/catchorg/Catch2.git
		GIT_TAG v2.13.1)

	FetchContent_GetProperties(Catch2)
	if(NOT catch2_POPULATED)
		set(FETCHCONTENT_QUIET OFF)
		FetchContent_Populate(catch2)
		set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${catch2_SOURCE_DIR}/contrib")
		add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
	endif()
endif()

add_executable(tests "main.cpp" "dungeonator_test.cpp")
target_link_libraries(tests PUBLIC Catch2::Catch2)
target_link_libraries(tests PUBLIC dungeonator)

include(CTest)
include(Catch)
catch_discover_tests(tests)
