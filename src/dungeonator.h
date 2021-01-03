#ifndef DUNGEONATOR_H
#define DUNGEONATOR_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define NUM_DIRECTIONS 4

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST,
} Directions;

void directionToDelta(Directions direction, long long *dx, long long *dy);

typedef bool **maze_t;

typedef struct {
  size_t width;
  size_t height;
  maze_t data;
} Grid;

maze_t mallocGrid(size_t width, size_t height);

void fillGrid(Grid *maze, bool value);

Grid createGrid(size_t width, size_t height);

void backtrackMaze(Grid *maze, size_t x, size_t y);

void printGrid(char *str, size_t bufsz, Grid *maze);

void freeGrid(Grid *maze);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif