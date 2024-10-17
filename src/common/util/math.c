#include <stdint.h>
#include "math.h"

int abs(const int x)
{
    if(x < 0) {
        return -x;
    }
    return x;
}


int pow(int x, const uint32_t n)
{
    if(n == 0) {
        return 1;
    }
    for (int i = 0; i < n - 1; i++) {
        x *= x;
    }
    return x;
}

int floor(const int x, const int multiple)
{
    return x - x % multiple;
}

int ceil(int x, int multiple)
{
    return floor(x, multiple) + multiple;
}
