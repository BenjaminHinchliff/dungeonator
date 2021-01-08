#include "generate.h"



bool contains(int* arr, size_t start, size_t end, int element) {
  for (size_t i = start; i < end; ++i) {
    if (arr[i] == element) {
      return true;
    }
  }
  return false;
}

bool generateDungeon(int width, int height, int placeTries, int additionalRoomSize, Grid *grid) {
  int region = 0;

  bool success = createGrid(width, height, grid);
  if (!success) {
    fprintf(stderr, "failed to create grid");
    return false;
  }
  placeRoomsInGrid(grid, placeTries, additionalRoomSize, &region);
  for (int y = 1; y < grid->height; y += 2) {
    for (int x = 1; x < grid->width; x += 2) {
      if (grid->data[y][x].tile == WALL) {
        backtrackMaze(grid, x, y, region++);
      }
    }
  }
  size_t num_connectors;
  Connector* connectors = getConnectors(grid, &num_connectors);
  if (!connectors) {
    fprintf(stderr, "something went wrong with getting connectors - generation failed");
    return grid;
  }
  int remaining_regions = region;
  int *merged = malloc(sizeof(int) * (region + 1ull));
  for (int i = 0; i <= region; ++i) {
    merged[i] = i;
  }
  while (remaining_regions > 1) {
    Connector* connector;
    do {
      connector = &connectors[uniform_distribution(0, (int)num_connectors)];
    } while (connector->used);

    Position fill = {
      .region = -1,
      .tile = DOOR,
    };

    grid->data[connector->y][connector->x] = fill;

    int num_regions;
    int* regions = mapMergedRegions(connector, merged, &num_regions);

    // merge
    for (int i = 0; i <= region; ++i) {
      if (contains(regions, 1, num_regions, merged[i])) {
        merged[i] = regions[0];
      }
    }

    remaining_regions -= num_regions - 1;

    for (int i = 0; i < num_connectors; ++i) {
      if (connectors[i].used) continue;
      Connector* new_conn = &connectors[i];
      int num_new_reg;
      mapMergedRegions(new_conn, merged, &num_new_reg);
      if (num_new_reg == 1) {
        connectors[i].used = true;
      }
    }
  }
  free(merged);
  free(connectors);
  return grid;
}
