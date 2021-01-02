#include "catch2/catch.hpp"
#include "dungeonator.h"

TEST_CASE("mallocMaze works", "[maze]") {
  Maze maze = createMaze(10, 6);
  printMaze(&maze);
  freeMaze(&maze);
}
