#ifndef DUNGEONATOR_H
#define DUNGEONATOR_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define NUM_DIRECTIONS 4

typedef enum DirectionsEnum {
  NORTH,
  EAST,
  SOUTH,
  WEST,
} Directions;

void directionToDelta(Directions direction, int *dx, int *dy);

typedef bool **maze_t;

typedef struct Grids {
  int width;
  int height;
  maze_t data;
} Grid;

maze_t mallocGrid(int width, int height);

void fillGrid(Grid *maze, int x1, int y1, int x2, int y2,
              bool value);

Grid createGrid(int width, int height);

void printGrid(char *str, int bufsz, Grid *maze);

void freeGrid(Grid *maze);

void backtrackMaze(Grid *maze, int x, int y);

typedef struct Rooms {
  int x1;
  int y1;
  int x2;
  int y2;
} Room;

bool isOverlapping(Room *A, Room *B);

void placeRoomsInGrid(Grid *grid, int tries, int roomAddSize);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif