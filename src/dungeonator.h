#ifndef DUNGEONATOR_H
#define DUNGEONATOR_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef bool **maze_t;

typedef struct {
  size_t width;
  size_t height;
  maze_t data;
} Maze;

maze_t mallocMaze(size_t width, size_t height);

void zeroMaze(Maze *maze);

Maze createMaze(size_t width, size_t height);

void printMaze(Maze *maze);

void freeMaze(Maze *maze);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif