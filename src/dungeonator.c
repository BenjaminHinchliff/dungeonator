#include "dungeonator.h"

void directionToDelta(Directions direction, int *dx, int *dy) {
  switch (direction) {
  case NORTH:
    *dx = 0;
    *dy = -1;
    break;
  case EAST:
    *dx = 1;
    *dy = 0;
    break;
  case SOUTH:
    *dx = 0;
    *dy = 1;
    break;
  case WEST:
    *dx = -1;
    *dy = 0;
    break;
  default:
    fprintf(stderr, "unknown direction!");
    break;
  }
}

maze_t mallocGrid(int width, int height) {
  maze_t maze = malloc(sizeof(bool *) * height);
  if (maze == NULL)
    return NULL;
  for (int y = 0; y < height; ++y) {
    maze[y] = malloc(sizeof(bool) * width);
    if (maze[y] == NULL)
      return NULL;
  }
  return maze;
}

void fillGrid(Grid *maze, int x1, int y1, int x2, int y2,
              bool value) {
  assert(x1 < x2 && y1 < y2 && "start x & y must be less than end x & y");
  assert(x2 < maze->width && y2 < maze->height && "must be smaller than board");
  for (int y = y1; y < maze->height; ++y) {
    for (int x = 0; x < maze->width; ++x) {
      maze->data[y][x] = value;
    }
  }
}

void shuffleDirections(Directions *array, int n) {
  if (n > 1) {
    for (int i = 0; i < n - 1; i++) {
      int j = i + rand() / (RAND_MAX / (n - i) + 1);
      Directions t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

bool noPassages(Grid *maze, int nx, int ny) {
  maze_t data = maze->data;
  return data[ny - 1][nx] && data[ny][nx + 1] && data[ny + 1][nx] &&
         data[ny][nx - 1];
}

Grid createGrid(int width, int height) {
  assert(width % 2 == 1 && height % 2 == 1 &&
         "width and height must be odd for mazes");
  assert(width >= 3 && height >= 3 && "maze must be at least 3 by 3");
  Grid maze = {
      .width = width,
      .height = height,
      .data = mallocGrid(width, height),
  };
  fillGrid(&maze, 0, 0, maze.width - 1, maze.height - 1, true);
  return maze;
}

void printGrid(char *str, size_t bufsz, Grid *maze) {
  if (bufsz > 0) {
    str[0] = '\0';
    --bufsz;
  }

  for (int y = 0; y < maze->height; ++y) {
    for (int x = 0; x < maze->width; ++x) {
      strncat(str, maze->data[y][x] ? "#" : ".", bufsz);
      if (--bufsz == 0)
        return;
    }
    strncat(str, "\n", bufsz);
    if (--bufsz == 0)
      return;
  }
}

void freeGrid(Grid *maze) {
  for (int y = 0; y < maze->height; ++y) {
    free(maze->data[y]);
  }
  free(maze->data);
}

void backtrackMaze(Grid *maze, int x, int y) {
  Directions directions[NUM_DIRECTIONS] = {NORTH, EAST, SOUTH, WEST};
  shuffleDirections(directions, NUM_DIRECTIONS);

  for (int i = 0; i < NUM_DIRECTIONS; ++i) {
    int dx, dy;
    directionToDelta(directions[i], &dx, &dy);
    int nx = x + 2 * dx;
    int ny = y + 2 * dy;

    if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height && noPassages(maze, nx, ny)) {
      maze->data[y][x] = false;
      maze->data[y + dy][x + dx] = false;
      maze->data[ny][nx] = false;
      backtrackMaze(maze, nx, ny);
    }
  }
}


int uniform_distribution(int rangeLow, int rangeHigh) {
  int range = rangeHigh - rangeLow + 1;
  int copies = RAND_MAX / range;
  int limit = range * copies;
  int myRand;
  do {
    myRand = rand();
  } while (myRand >= limit);
  return myRand / copies + rangeLow;
}

bool isOverlapping(Room *roomA, Room *roomB) {
  return roomA->x1 < roomB->x2 && roomA->x2 > roomB->x1 &&
         roomA->y1 < roomB->y2 && roomB->y2 > roomB->y1;
}

#define MAX_TRIES 500

void placeRoomsInGrid(Grid *grid, int tries, int roomAddSize) {
  Room rooms[MAX_TRIES];
  int room_num = 0;
  for (int i = 0; i < tries; ++i) {
    int size = uniform_distribution(1, 3 + roomAddSize) + 1;
    int rectangularity = uniform_distribution(0, 1 + size / 2) * 2;
    int width = size;
    int height = size;
    if (rand() % 2 == 0) {
      width += rectangularity;
    } else {
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
      if (isOverlapping(&room, &rooms[room_num])) {
        overlap = true;
        break;
      }
    }

    if (overlap)
      continue;

    rooms[room_num++] = room;

    fillGrid(grid, room.x1, room.y1, room.x2, room.y2, false);
    //printGrid(stdout, 65535, grid);
  }
}
