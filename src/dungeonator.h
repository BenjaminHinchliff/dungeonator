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

#include "grid.h"
#include "direction.h"
#include "maze.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  typedef struct Rooms {
    int x1;
    int y1;
    int x2;
    int y2;
  } Room;

  bool isOverlapping(Room* A, Room* B);

  void placeRoomsInGrid(Grid* grid, int tries, int roomAddSize);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !DUNGEONATOR_H