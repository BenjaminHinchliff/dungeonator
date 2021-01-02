#include "catch2/catch.hpp"
#include "dungeonator.h"

TEST_CASE("mallocMaze works", "[maze]") {
  Maze maze = createMaze(25, 15);
  printMaze(&maze);
  freeMaze(&maze);
}
