#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <stdbool.h>

#include "pcg_basic.h"

#include "direction.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  bool contains(int* arr, size_t start, size_t end, int element);

  void shuffleDirections(Direction* array, int n);

  int uniform_distribution(int rangeLow, int rangeHigh);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !RANDOM_H
