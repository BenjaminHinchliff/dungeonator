#ifndef CONNECTORS_H
#define CONNECTORS_H

#include "grid.h"
#include "direction.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct Connectors
{
  int regions[4];
  int num_regions;
  int x;
  int y;
  bool used;
} Connector;

#define CONNECTOR_ALLOC_SIZE 50

Connector* getConnectors(Grid* grid, size_t* num_connectors);
int* mapMergedRegions(Connector* connector, int* merged, int* num_regions);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !CONNECTORS_H
