cmake_minimum_required(VERSION 3.11)

project("dungeonator")

option(BUILD_TESTS "Build tests" OFF)
option(BUILD_DOCS "Build doxygen docs" OFF)

add_subdirectory("src")
if(BUILD_TESTS)
	if (NOT WIN32)
		# https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredBuild.md#ninja-generator
		set(CMAKE_UNITY_BUILD ON)
	endif()
	enable_testing()
	add_subdirectory("tests")
endif()
if(BUILD_DOCS)
	add_subdirectory("docs")
endif()
