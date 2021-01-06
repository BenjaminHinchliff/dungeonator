#include "maze.h"

void shuffleDirections(Direction* array, int n) {
  if (n > 1) {
    for (int i = 0; i < n - 1; i++) {
      int j = i + rand() / (RAND_MAX / (n - i) + 1);
      Direction t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

bool noPassages(Grid* maze, int nx, int ny) {
  maze_t data = maze->data;
  return data[ny - 1][nx] && data[ny][nx + 1] && data[ny + 1][nx] &&
    data[ny][nx - 1];
}

void backtrackMaze(Grid* maze, int x, int y) {
  Direction directions[NUM_DIRECTIONS] = { NORTH, EAST, SOUTH, WEST };
  shuffleDirections(directions, NUM_DIRECTIONS);

  for (int i = 0; i < NUM_DIRECTIONS; ++i) {
    int dx, dy;
    directionToDelta(directions[i], &dx, &dy);
    int nx = x + 2 * dx;
    int ny = y + 2 * dy;

    if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height &&
      noPassages(maze, nx, ny)) {
      maze->data[y][x] = false;
      maze->data[y + dy][x + dx] = false;
      maze->data[ny][nx] = false;
      backtrackMaze(maze, nx, ny);
    }
  }
}
