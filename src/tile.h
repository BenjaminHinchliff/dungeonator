#ifndef TILE_H
#define TILE_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  typedef enum Tiles {
    WALL,
    FLOOR,
    DOOR,
  } Tile;

  char getCharacterForTile(Tile tile);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !TILE_H
