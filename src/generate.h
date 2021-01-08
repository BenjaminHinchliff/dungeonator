#ifndef GENERATE_H
#define GENERATE_H

#include "grid.h"
#include "rooms.h"
#include "maze.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MAX_REGIONS MAX_ROOMS + 1

  Grid generateDungeon(int width, int height, int placeTries, int additionalRoomSize);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !GENERATE_H

