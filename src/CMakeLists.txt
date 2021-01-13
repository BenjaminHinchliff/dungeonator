cmake_minimum_required(VERSION 3.11)

# get mersenne twister rng
include(FetchContent)

FetchContent_Declare(
	pcg_fetch
	GIT_REPOSITORY https://github.com/imneme/pcg-c-basic.git
)

FetchContent_GetProperties(pcg_fetch)
if(NOT pcg_fetch_POPULATED)
	set(FETCHCONTENT_QUIET OFF)
	FetchContent_Populate(pcg_fetch)
	add_library(pcg STATIC "${pcg_fetch_SOURCE_DIR}/pcg_basic.c")
	target_include_directories(pcg PUBLIC "${pcg_fetch_SOURCE_DIR}")
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
target_link_libraries(${PROJECT_NAME} PUBLIC pcg)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${DUNGEONATOR_HDRS}")

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
	LIBRARY
	PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")
