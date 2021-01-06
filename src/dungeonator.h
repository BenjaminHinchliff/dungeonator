#ifndef DUNGEONATOR_H
#define DUNGEONATOR_H

/**
* \file dungeonator.h
* \brief main include file
* 
* the core file that has all of the logic function declarations provided by the library
*/

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

/**
* enum for the cardinal directions on a grid - used for the backtracking algorithm
*/
typedef enum Directions {
  NORTH,
  EAST,
  SOUTH,
  WEST,
} Direction;

/**
* convert the direction enum to a change in x and y, normalized, for use by the backtracking algorithm
*
* @param direction the direction to convert
*
* @param dx a pointer to a variable to write the change in x to, cannot be null
* @param dy a pointer to a variable to write the change in xy to, cannot be null
*/
void directionToDelta(Direction direction, int *dx, int *dy);

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

void printGridToString(char *str, int bufsz, Grid *maze);

void printGrid(Grid *maze);

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