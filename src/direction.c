#include "direction.h"

const Direction CARDINAL[NUM_DIRECTIONS] = { NORTH, EAST, SOUTH, WEST };

void directionToDelta(Direction direction, int* dx, int* dy) {
#ifndef NDEBUG
  assert(dx != NULL && dy != NULL && "output variables can't be NULL");
#endif // !NDEBUG
  switch (direction) {
  case NORTH:
    *dx = 0;
    *dy = -1;
    break;
  case EAST:
    *dx = 1;
    *dy = 0;
    break;
  case SOUTH:
    *dx = 0;
    *dy = 1;
    break;
  case WEST:
    *dx = -1;
    *dy = 0;
    break;
  default:
    fprintf(stderr, "unknown direction!");
    break;
  }
}
