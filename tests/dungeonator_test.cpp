#include "ApprovalTests.hpp"
#include "catch2/catch.hpp"
#include "dungeonator.h"

TEST_CASE("maze generation works", "[maze]") {
  pcg32_srandom(42u, 54u);
  Grid maze;
  bool success = createGrid(51, 27, &maze);
  if (!success) {
    throw std::runtime_error("failed to create grid");
  }
  backtrackMaze(&maze, 1, 1, 0);
  char buffer[2048];
  printGridToString(buffer, 2048, &maze);
  ApprovalTests::Approvals::verify(buffer);
  freeGrid(&maze);
}

TEST_CASE("rooms correctly overlap", "[rooms]") {
  SECTION("non-overlapping rooms are detected as such") {
    Room roomA{1, 2, 3, 4};
    Room roomB{5, 6, 7, 8};
    REQUIRE(!isOverlapping(&roomA, &roomB));
  }
  SECTION("overlapping rooms are detected as such") {
    Room roomA{1, 2, 3, 4};
    Room roomB{2, 3, 4, 5};
    REQUIRE(isOverlapping(&roomA, &roomB));
  }
}

TEST_CASE("room placing works", "[rooms]") {
  pcg32_srandom(42u, 54u);
  Grid grid;
  bool success = createGrid(51, 27, &grid);
  if (!success) {
    throw std::runtime_error("failed to create grid");
  }
  int region = 0;
  placeRoomsInGrid(&grid, 1000, 2, &region);
  char buffer[2048];
  printGridToString(buffer, 2048, &grid);
  ApprovalTests::Approvals::verify(buffer);
  freeGrid(&grid);
}

TEST_CASE("dungeon generation works", "[rooms]") {
  pcg32_srandom(42u, 54u);
  Grid grid;
  bool success = generateDungeon(51, 27, 1000, 2, &grid);
  if (!success) {
    throw std::runtime_error("failed to generate dungeon");
  }
  char buffer[2048];
  printGridToString(buffer, 2048, &grid);
  ApprovalTests::Approvals::verify(buffer);
  freeGrid(&grid);
}
