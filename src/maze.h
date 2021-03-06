#ifndef MAZE_H
#define MAZE_H

/**
* \file maze.h
* \brief the implementation file for maze generation code
* 
* the implementation file for maze generation code, currently only implementing recursive backtracking
*/

#include "direction.h"
#include "grid.h"
#include "util.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  /**
  * run recursive backtracking (aka depth-first search) on a grid to generate a maze
  * 
  * \param[in,out] grid the grid to run the algorithm on
  * \param[in] regions the regions array
  * \param[in] x the starting x position for backtracking
  * \param[in] y the starting y position for backtracking
  * \param[in] region the region of the maze
  * 
  * \warning can cause stack overflow if a grid is too large
  * \todo create stack based implementation to prevent this problem?
  */
  void backtrackMaze(Grid* grid, regions_t regions, int x, int y, int region);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !MAZE_H
