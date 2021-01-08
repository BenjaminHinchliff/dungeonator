#include "connectors.h"

Connector* getConnectors(Grid* grid, regions_t regions, size_t* num_connectors) {
  Connector* connectors = malloc(sizeof(Connector) * CONNECTOR_ALLOC_SIZE);
  if (!connectors) {
    fprintf(stderr, "failed to allocate connectors array");
    return NULL;
  }
  size_t reserved_connectors = CONNECTOR_ALLOC_SIZE;
  *num_connectors = 0;
  for (int y = 1; y < grid->height - 1; ++y) {
    for (int x = 1; x < grid->width - 1; ++x) {
      Connector connector = {
        .num_regions = 0,
        .x = x,
        .y = y,
        .used = false,
      };
      for (int i = 0; i < NUM_DIRECTIONS; ++i) {
        int dx, dy;
        directionToDelta(CARDINAL[i], &dx, &dy);
        int region = regions[y + dy][x + dx];
        if (region != -1 && !contains(connector.regions, 0, connector.num_regions, region)) {
          connector.regions[connector.num_regions++] = region;
        }
      }

      if (connector.num_regions > 1) {
        if (*num_connectors == reserved_connectors) {
          Connector* newConnectors = realloc(connectors, sizeof(Connector) * (reserved_connectors += CONNECTOR_ALLOC_SIZE));
          if (!newConnectors) {
            fprintf(stderr, "failed to reallocate connectors array");
            free(connectors);
            return NULL;
          }
          connectors = newConnectors;
        }
        connectors[(*num_connectors)++] = connector;
      }
    }
  }
  return connectors;
}

int* mapMergedRegions(Connector* connector, int* merged, int* num_regions) {
  // map together merged regions while deduplicating array
  static int regions[4];
  *num_regions = 0;
  for (int i = 0; i < connector->num_regions; ++i) {
    int region = merged[connector->regions[i]];
    if (!contains(regions, 0, *num_regions, region)) {
      regions[(*num_regions)++] = region;
    }
  }
  return regions;
}
