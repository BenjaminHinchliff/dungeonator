#include "ApprovalTests.hpp"
#include "catch2/catch.hpp"
#include "dungeonator.h"

TEST_CASE("maze generation works", "[maze]") {
  srand(42);
  Maze maze = createMaze(17, 11);
  char buffer[255];
  printMaze(buffer, 255, &maze);
  ApprovalTests::Approvals::verify(buffer);
  freeMaze(&maze);
}
