#include "maze.h"

bool isWall(Position* position) {
  return position->tile == WALL;
}

bool noPassages(Grid* maze, int nx, int ny) {
  maze_t data = maze->data;
  return isWall(&data[ny - 1][nx]) && isWall(&data[ny][nx + 1]) && isWall(&data[ny + 1][nx]) &&
    isWall(&data[ny][nx - 1]);
}

void backtrackMaze(Grid* maze, int x, int y, int region) {
  Direction directions[NUM_DIRECTIONS] = { NORTH, EAST, SOUTH, WEST };
  shuffleDirections(directions, NUM_DIRECTIONS);

  for (int i = 0; i < NUM_DIRECTIONS; ++i) {
    int dx, dy;
    directionToDelta(directions[i], &dx, &dy);
    int nx = x + 2 * dx;
    int ny = y + 2 * dy;

    if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height &&
      noPassages(maze, nx, ny)) {
      const Position fill = {
        .region = region,
        .tile = FLOOR,
      };
      maze->data[y][x] = fill;
      maze->data[y + dy][x + dx] = fill;
      maze->data[ny][nx] = fill;
      backtrackMaze(maze, nx, ny, region);
    }
  }
}
