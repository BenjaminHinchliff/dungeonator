#ifndef ROOMS_H
#define ROOMS_H

/**
* \file rooms.h
* \brief code for placing and detecting collisions of rooms
*/

#include "util.h"
#include "grid.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  /**
  * a struct to represent a room, used to determine overlapping
  */
  typedef struct Rooms {
    /**
    * the left x coordinate of a room
    */
    int x1;
    /**
    * the top y coordinate of a room
    */
    int y1;
    /**
    * the right x coordiante of a room
    */
    int x2;
    /**
    * the bottom y coordinate of a room
    */
    int y2;
  } Room;

  /**
  * test if two rooms are overlapping
  * 
  * \param[in] A a pointer to the frist room to test
  * \param[in] B a pointer to the second room to test
  * 
  * \returns if the rooms are overlapping
  */
  bool isOverlapping(Room* A, Room* B);

#ifndef ROOMS_ALLOC_SIZE
  /**
  * the default allocation size for the array of rooms, can be overrided
  */
#define ROOMS_ALLOC_SIZE 20
#endif

  /**
  * place rooms in a grid so that they don't overlap, and fill in their respective regions
  * 
  * \param[in,out] grid the grid to put the rooms onto
  * \param[in,out] regions the regions to place the rooms' regions onto
  * \param[in] tries the number of tries to places the rooms
  * \param[in] roomAddSize larger = bigger rooms
  * \param[in,out] a pointer to the region counter to determine the current region - will be mutated
  * 
  * \returns bool if the placing was successful (can fail on out of memory)
  */
  bool placeRoomsInGrid(Grid* grid, regions_t regions, int tries, int roomAddSize, int* region);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !ROOMS_H
