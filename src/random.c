#include "random.h"

void shuffleDirections(Direction* array, int n) {
  if (n > 1) {
    for (int i = 0; i < n - 1; i++) {
      int j = i + rand() / (RAND_MAX / (n - i) + 1);
      Direction t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

int uniform_distribution(int rangeLow, int rangeHigh) {
  int range = rangeHigh - rangeLow;
  int copies = RAND_MAX / range;
  int limit = range * copies;
  int myRand;
  do {
    myRand = rand();
  } while (myRand >= limit);
  return myRand / copies + rangeLow;
}
