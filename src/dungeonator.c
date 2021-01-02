#include "dungeonator.h"

maze_t mallocMaze(size_t width, size_t height) {
  maze_t maze = malloc(sizeof(bool *) * height);
  if (maze == NULL)
    return NULL;
  for (size_t y = 0; y < height; ++y) {
    maze[y] = malloc(sizeof(bool) * width);
    if (maze[y] == NULL)
      return NULL;
  }
  return maze;
}

void zeroMaze(Maze *maze) {
  for (size_t y = 0; y < maze->height; ++y) {
    for (size_t x = 0; x < maze->width; ++x) {
      maze->data[y][x] = false;
    }
  }
}

Maze createMaze(size_t width, size_t height) {
  Maze maze = {
      .width = width,
      .height = height,
      .data = mallocMaze(width, height),
  };
  zeroMaze(&maze);
  return maze;
}

void printMaze(Maze *maze) {
  for (size_t y = 0; y < maze->height; ++y) {
    for (size_t x = 0; x < maze->width; ++x) {
      printf("%c", maze->data[y][x] ? '#' : '.');
    }
    printf("\n");
  }
}

void freeMaze(Maze *maze) {
  for (size_t y = 0; y < maze->height; ++y) {
    free(maze->data[y]);
  }
  free(maze->data);
}
