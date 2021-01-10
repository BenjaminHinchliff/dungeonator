#include "grid.h"

void** malloc2d(int width, int height, size_t emntsize) {
  void** arr = malloc(sizeof(void*) * height);
  if (arr == NULL) {
    fprintf(stderr, "outer memory alloc failed");
    return NULL;
  }
  for (int y = 0; y < height; ++y) {
    arr[y] = malloc(emntsize * width);
    if (arr[y] == NULL) {
      fprintf(stderr, "failed to allocate inner memory for grid");
      return NULL;
    }
  }
  return arr;
}

data_t mallocGrid(int width, int height) {
  return (data_t)malloc2d(width, height, sizeof(Tile));
}

regions_t mallocRegions(int width, int height) {
  return (regions_t)malloc2d(width, height, sizeof(int));
}

void fillGrid(Grid* grid, int x1, int y1, int x2, int y2,
  Tile value) {
#ifndef NDEBUG
  assert(x1 < x2&& y1 < y2 && "start x & y must be less than end x & y");
  assert(x2 <= grid->width && y2 <= grid->height &&
    "must be smaller than board");
#endif // !NDEBUG
  for (int y = y1; y < y2; ++y) {
    for (int x = x1; x < x2; ++x) {
      grid->data[y][x] = value;
    }
  }
}

void fillRegion(regions_t regions, int x1, int y1, int x2, int y2,
  int value) {
#ifndef NDEBUG
  assert(x1 < x2&& y1 < y2 && "start x & y must be less than end x & y");
#endif // !NDEBUG
  for (int y = y1; y < y2; ++y) {
    for (int x = x1; x < x2; ++x) {
      regions[y][x] = value;
    }
  }
}

bool createGrid(int width, int height, Grid* grid) {
#ifndef NDEBUG
  assert(width % 2 == 1 && height % 2 == 1 &&
    "width and height must be odd for mazes");
  assert(width >= 3 && height >= 3 && "grid must be at least 3 by 3");
#endif // !NDEBUG
  data_t data = mallocGrid(width, height);
  if (data == NULL) {
    fprintf(stderr, "Failed to malloc grid");
    return false;
  }
  *grid = (Grid){
    .width = width,
    .height = height,
    .data = data
  };

  fillGrid(grid, 0, 0, grid->width, grid->height, WALL);
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
      sprintf(tileStr, "%c", getCharacterForTile(maze->data[y][x]));
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
      printf("%c", getCharacterForTile(maze->data[y][x]));
    }
    printf("\n");
  }
}

void debugPrintGrid(Grid* grid, regions_t regions) {
  printf("   ");
  for (int x = 0; x < grid->width; ++x) {
    printf("%2d", x);
  }
  printf("\n");
  for (int y = 0; y < grid->height; ++y) {
    printf("%2d ", y);
    for (int x = 0; x < grid->width; ++x) {
      Tile tile = grid->data[y][x];
      if (tile == FLOOR) {
        printf("%2X", regions[y][x]);
      }
      else {
        char c = getCharacterForTile(tile);
        printf("%c%c", c, c);
      }
    }
    printf("\n");
  }
  printf("---------------\n");
}

void free2d(void** arr, int height) {
  for (int y = 0; y < height; ++y) {
    free(arr[y]);
  }
  free(arr);
}

void freeGrid(Grid* maze) {
  free2d((void**)maze->data, maze->height);
}

void freeRegions(regions_t regions, int height) {
  free2d((void**)regions, height);
}
