#include "maze.h"

bool noPassages(Grid* maze, int nx, int ny) {
  for (int i = 0; i < NUM_DIRECTIONS; ++i) {
    int dx, dy;
    directionToDelta(CARDINAL[i], &dx, &dy);
    if (maze->data[ny + dy][nx + dx].tile != WALL) {
      return false;
    }
  }
  return true;
}

void backtrackMaze(Grid* maze, int x, int y, int region) {
  Direction directions[NUM_DIRECTIONS] = { NORTH, EAST, SOUTH, WEST };
  shuffleDirections(directions, NUM_DIRECTIONS);

  const Position fill = {
        .region = region,
        .tile = FLOOR,
  };
  maze->data[y][x] = fill;

  for (int i = 0; i < NUM_DIRECTIONS; ++i) {
    int dx, dy;
    directionToDelta(directions[i], &dx, &dy);
    int nx = x + 2 * dx;
    int ny = y + 2 * dy;

    if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height &&
      noPassages(maze, nx, ny)) {
      maze->data[y + dy][x + dx] = fill;
      maze->data[ny][nx] = fill;
      backtrackMaze(maze, nx, ny, region);
    }
  }
}
