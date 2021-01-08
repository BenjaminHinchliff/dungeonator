#ifndef GRID_H
#define GRID_H

/**
* \file grid.h
* \brief declaration file for grid functions
*
* a file full of grid functions to allow for operations
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "tile.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  /**
  * the type for the 2d grid data
  */
  typedef Tile** data_t;

  typedef int** regions_t;

  /**
  * a struct to allow access to both the data and width/height of the grid in one param
  */
  typedef struct Grids {
    /**
    * the width of the grid (2d array)
    */
    int width;
    /**
    * the height of the grid (2d array)
    */
    int height;
    /**
    * a pointer to the 2d grid data
    */
    data_t data;
  } Grid;

  /**
  * allocate the appropriate heap memory for a maze and cast it into an array - doesn't do any initialization.
  * reading from the array at this point is undefined behavior
  *
  * \param[in] width the width of the 2d array to allocate
  * \param[in] height the height of the 2d array to allocate
  *
  * \return a 2d pointer to the array
  */
  data_t mallocGrid(int width, int height);

  regions_t mallocRegions(int width, int height);

  /**
  * fill a rectangle inside a grid with a boolean value
  *
  * \param[in,out] grid the grid to fill
  * \param[in] x1 the left edge of the rectangle (inclusive)
  * \param[in] y1 the top edge of the rectangle (inclusive)
  * \param[in] x2 the right edge of the rectangle (exclusive)
  * \param[in] y2 the bottom edge of the rectangle (exclusive)
  * \param[in] value the boolean value to fill the grid with
  *
  * if you're confused what inclusive/exclusive means here,
  * basically it just doesn't fill all the way to the edge
  * since that creates unintuitive effects
  */
  void fillGrid(Grid* grid, int x1, int y1, int x2, int y2,
    Tile value);

  void fillRegion(regions_t regions, int x1, int y1, int x2, int y2,
    int value);

  /**
  * creates and returns a grid, initialized to be full of walls (true)
  *
  * \param[in] width the width of the grid
  * \param[in] height the height of the grid
  * \param[out] the created grid
  * 
  * \returns a boolean value indicating the success of the creation
  */
  bool createGrid(int width, int height, Grid* grid);

  /**
  * an alternative print function to allow printing a grid to a string
  *
  * \param[out] str the string to write the printed grid to
  * \param[in] bufsz the size of the output buffer, the function will only print part of the grid if it's not large enough
  * \param[in] grid the grid to print
  */
  void printGridToString(char* str, size_t bufsz, Grid* grid);

  /**
  * print a grid to stdout
  *
  * \param[in] grid the grid to print
  */
  void printGrid(Grid* grid);

  void debugPrintGrid(Grid* grid, regions_t regions);
  
  /**
  * free the memory to a grid
  * 
  * \param[in] the grid to free
  * 
  * using a grid after this point is undefined behavior
  */
  void freeGrid(Grid* grid);

  void freeRegions(regions_t regions, int height);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !GRID_H