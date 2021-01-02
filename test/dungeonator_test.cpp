#include "catch2/catch.hpp"
#include "dungeonator.h"

TEST_CASE("mallocMaze works", "[maze]") {
  constexpr size_t width = 10;
  constexpr size_t height = 6;
  maze_t maze = createMaze(width, height);
  printMaze(maze, width, height);
  freeMaze(maze, height);
}
