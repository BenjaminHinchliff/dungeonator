#include "dungeonator.h"

int uniform_distribution(int rangeLow, int rangeHigh) {
  int range = rangeHigh - rangeLow;
  int copies = RAND_MAX / range;
  int limit = range * copies;
  int myRand;
  do {
    myRand = rand();
  } while (myRand >= limit);
  return myRand / copies + rangeLow;
}

bool isOverlapping(Room* roomA, Room* roomB) {
  return roomA->x1 < roomB->x2&& roomA->x2 > roomB->x1 &&
    roomA->y1 < roomB->y2&& roomB->y2 > roomB->y1;
}

void placeRoomsInGrid(Grid* grid, int tries, int roomAddSize, int* region) {
  Room rooms[MAX_ROOMS];
  int room_num = 0;
  for (int i = 0; i < tries; ++i) {
    if (room_num == MAX_ROOMS)
      return;
    int size = uniform_distribution(1, 3 + roomAddSize) * 2 + 1;
    int rectangularity = uniform_distribution(0, 1 + size / 2) * 2;
    int width = size;
    int height = size;
    if (rand() % 2 == 0) {
      width += rectangularity;
    }
    else {
      height += rectangularity;
    }

    int x = uniform_distribution(0, (grid->width - width) / 2) * 2 + 1;
    int y = uniform_distribution(0, (grid->height - height) / 2) * 2 + 1;

    Room room = {
        .x1 = x,
        .y1 = y,
        .x2 = x + width,
        .y2 = y + height,
    };

    bool overlap = false;
    for (int i = 0; i < room_num; ++i) {
      if (isOverlapping(&room, &rooms[i])) {
        overlap = true;
        break;
      }
    }

    if (overlap)
      continue;

    Position position = {
      .tile = FLOOR,
      .region = (*region)++,
    };

    fillGrid(grid, room.x1, room.y1, room.x2, room.y2, position);
    rooms[room_num++] = room;
  }
}

typedef struct Connectors
{
  int regions[4];
  int num_regions;
  int x;
  int y;
  bool used;
} Connector;

#define CONNECTOR_ALLOC_SIZE 100

bool contains(int* arr, size_t start, size_t end, int element) {
  for (size_t i = start; i < end; ++i) {
    if (arr[i] == element) {
      return true;
    }
  }
  return false;
}

Connector* getConnectors(Grid* grid, size_t* num_connectors) {
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
        Position* pos = &grid->data[y + dy][x + dx];
        if (pos->region != -1 && !contains(connector.regions, 0, connector.num_regions, pos->region)) {
          connector.regions[connector.num_regions++] = pos->region;
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

int* mapMergedRegions(Connector *connector, int *merged, int *num_regions) {
  // map together merged regions while deduplicating array
  int regions[4];
  *num_regions = 0;
  for (int i = 0; i < connector->num_regions; ++i) {
    int region = merged[connector->regions[i]];
    if (!contains(regions, 0, *num_regions, region)) {
      regions[(*num_regions)++] = region;
    }
  }
  return regions;
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
    int *regions = mapMergedRegions(connector, merged, &num_regions);

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
