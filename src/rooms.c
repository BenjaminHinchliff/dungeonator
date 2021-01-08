#include "rooms.h"

bool isOverlapping(Room* roomA, Room* roomB) {
  return roomA->x1 < roomB->x2&& roomA->x2 > roomB->x1 &&
    roomA->y1 < roomB->y2&& roomB->y2 > roomB->y1;
}

bool placeRoomsInGrid(Grid* grid, regions_t regions, int tries, int roomAddSize, int* region) {
  Room *rooms = malloc(sizeof(Room) * ROOMS_ALLOC_SIZE);
  if (rooms == NULL) {
    fprintf(stderr, "failed to allocate rooms array");
    return false;
  }
  size_t rooms_capacity = ROOMS_ALLOC_SIZE;
  int room_num = 0;
  for (int i = 0; i < tries; ++i) {
    if (room_num == ROOMS_ALLOC_SIZE) {
      Room* newRooms = realloc(rooms, sizeof(Room) * (rooms_capacity += ROOMS_ALLOC_SIZE));
      if (newRooms == NULL) {
        fprintf(stderr, "failed to expand rooms array");
        free(rooms);
        return false;
      }
      rooms = newRooms;
    }
    int size = uniform_distribution(1, 3 + roomAddSize) * 2 + 1;
    int rectangularity = uniform_distribution(0, 1 + size / 2) * 2;
    int width = size;
    int height = size;
    if (uniform_distribution(0, 2) == 0) {
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

    if (!overlap) {
      fillGrid(grid, room.x1, room.y1, room.x2, room.y2, FLOOR);
      fillRegion(regions, room.x1, room.y1, room.x2, room.y2, (*region)++);
      rooms[room_num++] = room;
    }
  }
  free(rooms);
  return true;
}
