#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <stdbool.h>

#include "pcg_basic.h"

#include "direction.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  /**
  * test if an int array contains an int
  * 
  * time complexity O(n) (obviously)
  * 
  * \param[in] arr the array to check
  * \param[in] the start index to check from
  * \param[in] the end index to check to
  * \param[in] the element to check for
  * 
  * \returns whether the array contains the element
  */
  bool contains(int* arr, size_t start, size_t end, int element);

  /**
  * shuffle the array of directions
  * 
  * \param[in,out] the array to shuffle
  * \param[in] n the length of the array
  */
  void shuffleDirections(Direction* array, int n);

  /**
  * get a random number in a uniform distribution of [rangeLow, rangeHigh)
  * 
  * \param[in] rangeLow the lower number in the range
  * \param[in] rangeHigh the higher number in the range
  * 
  * \returns a random int in the range
  */
  int uniform_distribution(int rangeLow, int rangeHigh);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !RANDOM_H
