#include "generate.h"



bool contains(int* arr, size_t start, size_t end, int element) {
  for (size_t i = start; i < end; ++i) {
    if (arr[i] == element) {
      return true;
    }
  }
  return false;
}

Grid generateDungeon(int width, int height, int placeTries, int additionalRoomSize) {
  int region = 0;

  Grid grid = createGrid(width, height);
  placeRoomsInGrid(&grid, placeTries, additionalRoomSize, &region);
  for (int y = 1; y < grid.height; y += 2) {
    for (int x = 1; x < grid.width; x += 2) {
      if (grid.data[y][x].tile == WALL) {
        backtrackMaze(&grid, x, y, region++);
      }
    }
  }
  size_t num_connectors;
  Connector* connectors = getConnectors(&grid, &num_connectors);
  if (!connectors) {
    fprintf(stderr, "something went wrong with getting connectors - generation failed");
    return grid;
  }
  for (size_t i = 0; i < num_connectors; ++i) {
    Connector* conn = &connectors[i];
    printf("%llu - Connector at x: %d, y: %d\n", i, conn->x, conn->y);
  }
  printf("%d\n", region);
  int remaining_regions = region;
  int merged[MAX_REGIONS];
  for (int i = 0; i < MAX_REGIONS; ++i) {
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

    grid.data[connector->y][connector->x] = fill;

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
  for (size_t i = 0; i < num_connectors; ++i) {
    if (connectors[i].used) continue;
    Connector* conn = &connectors[i];
    printf("%llu - Connector at x: %d, y: %d\n", i, conn->x, conn->y);
  }
  free(connectors);
  return grid;
}
