﻿#include "dungeonator.h"

void directionToDelta(Directions direction, long long *dx, long long *dy) {
  switch (direction) {
  case NORTH:
    *dx = 0;
    *dy = -1;
    break;
  case EAST:
    *dx = 1;
    *dy = 0;
    break;
  case SOUTH:
    *dx = 0;
    *dy = 1;
    break;
  case WEST:
    *dx = -1;
    *dy = 0;
    break;
  default:
    fprintf(stderr, "unknown direction!");
    break;
  }
}

maze_t mallocGrid(size_t width, size_t height) {
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

void fillGrid(Grid *maze, bool value) {
  for (size_t y = 0; y < maze->height; ++y) {
    for (size_t x = 0; x < maze->width; ++x) {
      maze->data[y][x] = value;
    }
  }
}

void shuffleDirections(Directions *array, size_t n) {
  if (n > 1) {
    size_t i;
    for (i = 0; i < n - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      Directions t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

bool noPassages(Grid *maze, size_t nx, size_t ny) {
  maze_t data = maze->data;
  return data[ny - 1][nx] && data[ny][nx + 1] && data[ny + 1][nx] &&
         data[ny][nx - 1];
}

void backtrackMaze(Grid *maze, size_t x, size_t y) {
  Directions directions[NUM_DIRECTIONS] = {NORTH, EAST, SOUTH, WEST};
  shuffleDirections(directions, NUM_DIRECTIONS);

  for (size_t i = 0; i < NUM_DIRECTIONS; ++i) {
    long long dx, dy;
    directionToDelta(directions[i], &dx, &dy);
    size_t nx = x + 2 * dx;
    size_t ny = y + 2 * dy;

    if (nx < maze->width && ny < maze->height && noPassages(maze, nx, ny)) {
      maze->data[y][x] = false;
      maze->data[y + dy][x + dx] = false;
      maze->data[ny][nx] = false;
      backtrackMaze(maze, nx, ny);
    }
  }
}

Grid createGrid(size_t width, size_t height) {
  assert(width % 2 == 1 && height % 2 == 1 &&
         "width and height must be odd for mazes");
  assert(width >= 3 && height >= 3 && "maze must be at least 3 by 3");
  Grid maze = {
      .width = width,
      .height = height,
      .data = mallocGrid(width, height),
  };
  fillGrid(&maze, true);
  return maze;
}

void printGrid(char *str, size_t bufsz, Grid *maze) {
  if (bufsz > 0) {
    str[0] = '\0';
    --bufsz;
  }

  for (size_t y = 0; y < maze->height; ++y) {
    for (size_t x = 0; x < maze->width; ++x) {
      strncat(str, maze->data[y][x] ? "#" : ".", bufsz);
      if (--bufsz == 0)
        return;
    }
    strncat(str, "\n", bufsz);
    if (--bufsz == 0)
      return;
  }
}

void freeGrid(Grid *maze) {
  for (size_t y = 0; y < maze->height; ++y) {
    free(maze->data[y]);
  }
  free(maze->data);
}
