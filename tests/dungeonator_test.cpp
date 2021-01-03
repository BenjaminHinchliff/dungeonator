#include "ApprovalTests.hpp"
#include "catch2/catch.hpp"
#include "dungeonator.h"

TEST_CASE("maze generation works", "[maze]") {
  srand(42);
  Grid maze = createGrid(51, 27);
  backtrackMaze(&maze, 1, 1);
  char buffer[2048];
  printGrid(buffer, 2048, &maze);
  ApprovalTests::Approvals::verify(buffer);
  freeGrid(&maze);
}
