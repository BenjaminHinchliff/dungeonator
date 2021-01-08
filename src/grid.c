#include "grid.h"

maze_t mallocGrid(int width, int height) {
  maze_t maze = malloc(sizeof(Position*) * height);
  if (maze == NULL)
    return NULL;
  for (int y = 0; y < height; ++y) {
    maze[y] = malloc(sizeof(Position) * width);
    if (maze[y] == NULL)
      return NULL;
  }
  return maze;
}

void fillGrid(Grid* maze, int x1, int y1, int x2, int y2, Position value) {
#ifndef NDEBUG
  assert(x1 < x2&& y1 < y2 && "start x & y must be less than end x & y");
  assert(x2 <= maze->width && y2 <= maze->height &&
    "must be smaller than board");
#endif // !NDEBUG
  for (int y = y1; y < y2; ++y) {
    for (int x = x1; x < x2; ++x) {
      maze->data[y][x] = value;
    }
  }
}

Grid createGrid(int width, int height) {
#ifndef NDEBUG
  assert(width % 2 == 1 && height % 2 == 1 &&
    "width and height must be odd for mazes");
  assert(width >= 3 && height >= 3 && "maze must be at least 3 by 3");
#endif // !NDEBUG
  Grid maze = {
      .width = width,
      .height = height,
      .data = mallocGrid(width, height),
  };
  Position fill = {
    .region = -1,
    .tile = WALL,
  };
  fillGrid(&maze, 0, 0, maze.width, maze.height, fill);
  return maze;
}

void printGridToString(char* str, size_t bufsz, Grid* maze) {
  if (bufsz > 0) {
    str[0] = '\0';
    --bufsz;
  }

  for (int y = 0; y < maze->height; ++y) {
    for (int x = 0; x < maze->width; ++x) {
      strncat(str, maze->data[y][x].tile == WALL ? "#" : ".", bufsz);
      if (--bufsz == 0)
        return;
    }
    strncat(str, "\n", bufsz);
    if (--bufsz == 0)
      return;
  }
}

void printGrid(Grid* maze) {
  for (int y = 0; y < maze->height; ++y) {
    for (int x = 0; x < maze->width; ++x) {
      Position* pos = &maze->data[y][x];
      if (pos->tile == WALL) {
        printf("#");
      }
      else if (pos->region != -1) {
        printf("%x", pos->region);
      }
      else {
        printf(".");
      }
    }
    printf("\n");
  }
}

void freeGrid(Grid* maze) {
  for (int y = 0; y < maze->height; ++y) {
    free(maze->data[y]);
  }
  free(maze->data);
}
