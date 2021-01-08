#ifndef GENERATE_H
#define GENERATE_H

#include "grid.h"
#include "rooms.h"
#include "maze.h"
#include "connectors.h"
#include "dead_ends.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  bool generateDungeon(Grid* grid, int width, int height, int placeTries, int additionalRoomSize);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !GENERATE_H

