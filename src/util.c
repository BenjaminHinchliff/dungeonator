#include "util.h"

bool contains(int* arr, size_t start, size_t end, int element) {
  for (size_t i = start; i < end; ++i) {
    if (arr[i] == element) {
      return true;
    }
  }
  return false;
}

void shuffleDirections(Direction* array, int n) {
  if (n > 1) {
    for (int i = 0; i < n - 1; ++i) {
      int j = i + pcg32_boundedrand(n - i);
      Direction t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

int uniform_distribution(int rangeLow, int rangeHigh) {
#ifndef NDEBUG
  assert(rangeLow < rangeHigh && "lower part must be lower");
#endif // !NDEBUG
  return rangeLow + pcg32_boundedrand(rangeHigh - rangeLow);
}
