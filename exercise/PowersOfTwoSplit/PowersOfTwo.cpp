/**
 * @brief raiseToPower
 * Usage: int p = raiseToPower(n, k);
 * ----------------------------------
 * Return the integer n raised to the kth power.
 */

#include <iostream>
#include"PowersOfTwo.h"
int raiseToPower(int n, int k) {
  int result = 1;
  for (size_t i = 0; i < k; i++) {
    result *= n;
  }
  return result;
}
