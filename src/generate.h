#ifndef GENERATE_H
#define GENERATE_H

/**
* \file generate.h
* \brief code pulling together all the parts to generate the dungeon
*/

#include "grid.h"
#include "rooms.h"
#include "maze.h"
#include "connectors.h"
#include "dead_ends.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  /**
  * generate a dungeon
  * 
  * \param[out] grid the grid to output the dungeon to
  * \param[in] width the width of the dungeon
  * \param[in] height the height of the dungeon
  * \param[in] placeTries the number of times to attempt to place rooms - this can be thought of as the density of rooms
  * \param[in] additionalRoomSize the amount of size to add to the room (3 + additional) - larger means bigger rooms
  * 
  * \returns whether the generation was successful
  */
  bool generateDungeon(Grid* grid, int width, int height, int placeTries, int additionalRoomSize);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !GENERATE_H

