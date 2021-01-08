#include "grid.h"

maze_t mallocGrid(int width, int height) {
  maze_t maze = malloc(sizeof(Position*) * height);
  if (maze == NULL) {
    fprintf(stderr, "failed to allocate outer memory for grid");
    return NULL;
  }
  for (int y = 0; y < height; ++y) {
    maze[y] = malloc(sizeof(Position) * width);
    if (maze[y] == NULL) {
      fprintf(stderr, "failed to allocate inner memory for grid");
      return NULL;
    }
  }
  return maze;
}

void fillGrid(Grid* maze, int x1, int y1, int x2, int y2, Position value) {
#ifndef NDEBUG
  assert(x1 < x2&& y1 < y2 && "start x & y must be less than end x & y");
  assert(x2 <= maze->width && y2 <= maze->height &&
    "must be smaller than board");
#endif // !NDEBUG
  for (int y = y1; y < y2; ++y) {
    for (int x = x1; x < x2; ++x) {
      maze->data[y][x] = value;
    }
  }
}

bool createGrid(int width, int height, Grid* grid) {
#ifndef NDEBUG
  assert(width % 2 == 1 && height % 2 == 1 &&
    "width and height must be odd for mazes");
  assert(width >= 3 && height >= 3 && "grid must be at least 3 by 3");
#endif // !NDEBUG
  maze_t data = mallocGrid(width, height);
  if (data == NULL) {
    fprintf(stderr, "Failed to malloc grid");
    return false;
  }
  *grid = (Grid){
    .width = width,
    .height = height,
    .data = data
  };

  Position fill = {
    .region = -1,
    .tile = WALL,
  };
  fillGrid(grid, 0, 0, grid->width, grid->height, fill);
  return grid;
}

void printGridToString(char* str, size_t bufsz, Grid* maze) {
  if (bufsz > 1) {
    str[0] = '\0';
    --bufsz;
  }

  for (int y = 0; y < maze->height; ++y) {
    for (int x = 0; x < maze->width; ++x) {
      char tileStr[2];
      sprintf(tileStr, "%c", getCharacterForTile(maze->data[y][x].tile));
      strncat(str, tileStr, bufsz);
      if (--bufsz == 0)
        return;
    }
    strncat(str, "\n", bufsz);
    if (--bufsz == 0)
      return;
  }
}

void printGrid(Grid* maze) {
  for (int y = 0; y < maze->height; ++y) {
    for (int x = 0; x < maze->width; ++x) {
      printf("%c", getCharacterForTile(maze->data[y][x].tile));
    }
    printf("\n");
  }
}

void debugPrintGrid(Grid* grid) {
  printf("   ");
  for (int x = 0; x < grid->width; ++x) {
    printf("%2d", x);
  }
  printf("\n");
  for (int y = 0; y < grid->height; ++y) {
    printf("%2d ", y);
    for (int x = 0; x < grid->width; ++x) {
      Position* pos = &grid->data[y][x];
      if (pos->tile == FLOOR) {
        printf("%2X", pos->region);
      }
      else {
        char c = getCharacterForTile(grid->data[y][x].tile);
        printf("%c%c", c, c);
      }
    }
    printf("\n");
  }
  printf("---------------\n");
}

void freeGrid(Grid* maze) {
  for (int y = 0; y < maze->height; ++y) {
    free(maze->data[y]);
  }
  free(maze->data);
}
