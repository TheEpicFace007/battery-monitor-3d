#include "utility.h"
#include <random>
#include <3ds.h>

void sleep(int ms) {
    svcSleepThread(ms * 1000000);
}

void randomseed(int seed) {
    srand(seed);
}

int randint(int min, int max) {
    return rand() % (max - min + 1) + min;
}

std::vector<u8> interpolateColor(u32 color1, u32 color2, int steps) {
    std::vector<u8> colors;
    u8 r1 = (color1 >> 24) & 0xFF;
    u8 g1 = (color1 >> 16) & 0xFF;
    u8 b1 = (color1 >> 8) & 0xFF;
    u8 r2 = (color2 >> 24) & 0xFF;
    u8 g2 = (color2 >> 16) & 0xFF;
    u8 b2 = (color2 >> 8) & 0xFF;
    for (int i = 0; i < steps; i++) {
        u8 r = r1 + (r2 - r1) * i / steps;
        u8 g = g1 + (g2 - g1) * i / steps;
        u8 b = b1 + (b2 - b1) * i / steps;
        colors.push_back(r);
        colors.push_back(g);
        colors.push_back(b);
    }
    return colors;
}