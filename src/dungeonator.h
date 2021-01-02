#ifndef DUNGEONATOR_H
#define DUNGEONATOR_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef bool** maze_t;

maze_t mallocMaze(size_t width, size_t height);

maze_t zeroMaze(maze_t maze, size_t width, size_t height);

maze_t createMaze(size_t width, size_t height);

void printMaze(maze_t maze, size_t width, size_t height);

void freeMaze(maze_t maze, size_t height);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif