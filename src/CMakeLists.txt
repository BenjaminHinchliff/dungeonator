cmake_minimum_required(VERSION 3.11)

# get mersenne twister rng
include(FetchContent)

FetchContent_Declare(
	pcg_basic
	GIT_REPOSITORY https://github.com/imneme/pcg-c-basic.git
)

FetchContent_GetProperties(pcg_basic)
if(NOT pcg_POPULATED)
	set(FETCHCONTENT_QUIET OFF)
	FetchContent_Populate(pcg_basic)
	add_library(pcg_basic STATIC "${pcg_basic_SOURCE_DIR}/pcg_basic.c")
	target_include_directories(pcg_basic PUBLIC "${pcg_basic_SOURCE_DIR}")

	set_target_properties(pcg_basic PROPERTIES PUBLIC_HEADER "${pcg_basic_SOURCE_DIR}/pcg_basic.h")

	include(GNUInstallDirs)
	install(TARGETS pcg_basic
		LIBRARY
		PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")
endif()

set(DUNGEONATOR_SRCS
	"grid.c"
	"direction.c"
	"maze.c"
	"rooms.c"
	"util.c"
	"generate.c"
	"tile.c"
	"connectors.c"
	"dead_ends.c")

set(DUNGEONATOR_HDRS
	"dungeonator.h"
	"grid.h"
	"direction.h"
	"maze.h"
	"rooms.h"
	"util.h"
	"generate.h"
	"tile.h"
	"connectors.h"
	"dead_ends.h")

add_library(${PROJECT_NAME} STATIC ${DUNGEONATOR_SRCS} ${DUNGEONATOR_HDRS})
target_include_directories(${PROJECT_NAME} PUBLIC ".")
target_link_libraries(${PROJECT_NAME} PUBLIC pcg_basic)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${DUNGEONATOR_HDRS}")

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
	LIBRARY
	PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")
