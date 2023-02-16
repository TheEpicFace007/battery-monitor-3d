#pragma once
#include <vector>
#include <3ds.h>

void sleep(int ms);
void randomseed(int seed);
int randint(int min, int max);
std::vector<u8> interpolateColor(u32 color1, u32 color2, int steps);
