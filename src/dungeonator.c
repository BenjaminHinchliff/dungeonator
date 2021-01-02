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

maze_t zeroMaze(maze_t maze, size_t width, size_t height) {
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      maze[y][x] = false;
    }
  }

  return maze;
}

maze_t createMaze(size_t width, size_t height) {
  maze_t maze = mallocMaze(width, height);
  zeroMaze(maze, width, height);
  return maze;
}

void printMaze(maze_t maze, size_t width, size_t height) {
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      printf("%c", maze[y][x] ? '#' : '.');
    }
    printf("\n");
  }
}

void freeMaze(maze_t maze, size_t height) {
  for (size_t y = 0; y < height; ++y) {
    free(maze[y]);
  }
  free(maze);
}
