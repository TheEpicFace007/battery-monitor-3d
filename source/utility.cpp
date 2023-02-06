#include "utility.h"
#include <3ds.h>

void sleep(int ms)
{
    svcSleepThread(ms * 1000000);
}