#include "utility.h"
#include <random>
#include <3ds.h>

void sleep(int ms)
{
    svcSleepThread(ms * 1000000);
}

void randomseed(int seed)
{
    srand(seed);
}

int randint(int min, int max)
{
    return rand() % (max - min + 1) + min;
}