#ifndef TILE_H
#define TILE_H

/**
* \file tile.h
* \brief the include file for the potential tiles in a grid
*/

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  /**
  * the types of tiles that can be part of a grid
  */
  typedef enum Tiles {
    /**
    * a wall tile (doesn't have to be next to floor)
    */
    WALL,
    /**
    * air/floor tile
    */
    FLOOR,
    /**
    * another name for a connection between two rooms
    */
    DOOR,
  } Tile;

  /**
  * get a character from the tile enum
  * 
  * WALL -> '#'
  * FLOOR -> '.'
  * DOOR -> '+'
  * 
  * \param[in] tile the tile to get the character for 
  * 
  * \returns the character
  */
  char getCharacterForTile(Tile tile);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !TILE_H
