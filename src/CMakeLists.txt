cmake_minimum_required(VERSION 3.11)

set(DUNGEONATOR_SRCS
	"grid.c"
	"direction.c"
	"maze.c"
	"rooms.c"
	"random.c"
	"generate.c")

set(DUNGEONATOR_HDRS
	"dungeonator.h"
	"grid.h"
	"direction.h"
	"maze.h"
	"rooms.h"
	"random.h"
	"generate.h")

add_library(${PROJECT_NAME} ${DUNGEONATOR_SRCS} ${DUNGEONATOR_HDRS})
target_include_directories(${PROJECT_NAME} PUBLIC ".")
