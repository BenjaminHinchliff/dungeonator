#ifndef DEAD_ENDS_H
#define DEAD_ENDS_H

#include "direction.h"
#include "grid.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  void remove_dead_ends(Grid* grid);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !DEAD_ENDS_H
