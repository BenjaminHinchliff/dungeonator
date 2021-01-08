#include "rooms.h"

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