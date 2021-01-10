#ifndef DIRECTION_H
#define DIRECTION_H

/**
* \file direction.h
* \brief declaration file for directions enum
*/

#include <assert.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
* the number of directions in the enum
*/
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
  * a constant array of cardinal directions
  */
  extern const Direction CARDINAL[NUM_DIRECTIONS];

  /**
  * convert the direction enum to a change in x and y, normalized, for use by the backtracking algorithm.
  *
  * \param[in] direction the direction to convert
  *
  * \param[out] dx a pointer to a variable to write the change in x to, cannot be null
  * \param[out] dy a pointer to a variable to write the change in xy to, cannot be null
  */
  void directionToDelta(Direction direction, int* dx, int* dy);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !DIRECTION_H
