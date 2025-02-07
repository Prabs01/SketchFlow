#pragma once

#include<SDL.h>

struct Color {
    Uint8 r, g, b, a;

    Color():r(0),b(0),g(0),a(0){};

    Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}

    // Convert Color to Uint32 (ARGB)
    Uint32 toUint32() const {
        return (a << 24) | (r << 16) | (g << 8) | b;
    }
};

const Color red(255, 0, 0);
const Color green(0, 255, 0);
const Color blue(0, 0, 255);
const Color white(255, 255, 255);
const Color black(0, 0, 0);
const Color gray(128, 128, 128);
const Color yellow(255, 255, 0);
const Color cyan(0, 255, 255);
const Color magenta(255, 0, 255);
const Color orange(255, 165, 0);
const Color pink(255, 192, 203);
const Color brown(165, 42, 42);
const Color purple(128, 0, 128);
const Color violet(238, 130, 238);
const Color indigo(75, 0, 130);
const Color lime(0, 255, 0);
const Color lightGray(211, 211, 211);
const Color transparent(0,0,0,0);