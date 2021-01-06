cmake_minimum_required(VERSION 3.11)

set(DUNGEONATOR_SRCS
	"dungeonator.c"
	"grid.c"
	"direction.c"
	"maze.c")

set(DUNGEONATOR_HDRS
	"dungeonator.h"
	"grid.h"
	"direction.h"
	"maze.h")

add_library(${PROJECT_NAME} ${DUNGEONATOR_SRCS} ${DUNGEONATOR_HDRS})
target_include_directories(${PROJECT_NAME} PUBLIC ".")
