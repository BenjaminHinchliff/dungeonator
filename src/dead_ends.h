#ifndef DEAD_ENDS_H
#define DEAD_ENDS_H

/**
* \file dead_ends.h
* \brief code for removing the dead-ends of the dungeon
*/

#include "direction.h"
#include "grid.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  /**
  * remove dead ends inside grid based on checking if the number of exits is equal to 1
  * 
  * \param[in] grid the grid to remove the dead-ends of
  */
  void remove_dead_ends(Grid* grid);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !DEAD_ENDS_H
