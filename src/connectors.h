#ifndef CONNECTORS_H
#define CONNECTORS_H

/**
* \file connectors.h
* \brief file for connections between regions (doors)
*/

#include <stdbool.h>

#include "grid.h"
#include "direction.h"
#include "util.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
* A struct to represent a connection between 2 regions
*/
typedef struct Connectors
{
  /**
  * an array for the specific regions connected, with a max size of NUM_DIRECTIONS
  */
  int regions[NUM_DIRECTIONS];
  /**
  * the number of regions held by the array
  */
  int num_regions;
  /**
  * the x position of the connector
  */
  int x;
  /**
  * the y position of the connector
  */
  int y;
  /**
  * a boolean value to indicate if the connector has already been used
  */
  bool used;
} Connector;

#ifndef CONNECTOR_ALLOC_SIZE
/**
* the default size to expand the connector array by each time.
* can be overrided by the user by defining it themselves
*/
#define CONNECTOR_ALLOC_SIZE 50
#endif // !CONNECTOR_ALLOC_SIZE

/**
* given a grid (for size information) and a list of the various regions, get the potential connectors between them
* 
* \param[in] grid a pointer to a grid to get width and height info
* \param[in] regions the 2d regions array to determine which region a tile is in
* \param[out] num_connectors the number of connectors found - make sure to use this to avoid undefined behavior
* 
* \returns a pointer the the malloced array of connectors (remember to free it!)
*/
Connector* getConnectors(Grid* grid, regions_t regions, size_t* num_connectors);

/**
* take the region for a connector and use a mapping array to process potential merging it's regions
* also deduplicates array, so each region will only be included once
* 
* \param[in] connector a pointer to the connector to map the regions of
* \param[in] merged an array that will be used to map the various regions
* \param[out] num_regions the number of regions in the ouput array
* 
* \returns a pointer to the array of mapped regions
* 
* \note similar to the connector, the returned array actually has an allocated length of NUM_DIRECTIONS, and is static.
* this was done to avoid extra mallocs, but does mean that if you call this twice and assign to two pointers, they will actually both
* point to the result of the second call. Just be wary of that.
*/
int* mapMergedRegions(Connector* connector, int* merged, int* num_regions);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !CONNECTORS_H
