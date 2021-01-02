#include "ApprovalTests.hpp"
#include "catch2/catch.hpp"
#include "dungeonator.h"

TEST_CASE("maze generation works", "[maze]") {
  srand(42);
  Maze maze = createMaze(51, 27);
  char buffer[2048];
  printMaze(buffer, 2048, &maze);
  ApprovalTests::Approvals::verify(buffer);
  freeMaze(&maze);
}
