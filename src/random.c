#include "random.h"

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
  return rangeLow + pcg32_boundedrand(rangeHigh);
}
