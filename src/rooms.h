#ifndef ROOMS_H
#define ROOMS_H

#include "random.h"
#include "grid.h"

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

#ifndef ROOMS_ALLOC_SIZE
#define ROOMS_ALLOC_SIZE 20
#endif

  bool placeRoomsInGrid(Grid* grid, int tries, int roomAddSize, int* region); 

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !ROOMS_H
