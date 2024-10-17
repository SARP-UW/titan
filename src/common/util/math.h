#include <stdint.h>
// 8, 32, 64
#ifndef MATH_H
#define MATH_H

int abs(int x);
int pow(int x, uint32_t n);

/**
 * @param x
 * @param multiple
 * @return x floored to the nearest multiple of "multiple"
 * eg: floor(10, 5) = 10.  floor(10, 4) = 8
 */
int floor(int x, int multiple);
int ceil(int x, int multiple);




#endif //MATH_H
