#ifndef Color_H
#define Color_H

#include <cstdint>

typedef uint8_t u8;

struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;

    Color(u8 _r, u8 _g, u8 _b, u8 _a):r(_r), g(_g), b(_b), a(_a){};
};

const Color BASE_COLORS[] = {
    Color(0x28, 0x28, 0x28, 0xFF),
    Color(0x2D, 0x99, 0x99, 0xFF),
    Color(0x99, 0x99, 0x2D, 0xFF),
    Color(0x99, 0x2D, 0x99, 0xFF),
    Color(0x2D, 0x99, 0x51, 0xFF),
    Color(0x99, 0x2D, 0x2D, 0xFF),
    Color(0x2D, 0x63, 0x99, 0xFF),
    Color(0x99, 0x63, 0x2D, 0xFF)
};

const Color LIGHT_COLORS[] = {
    Color(0x28, 0x28, 0x28, 0xFF),
    Color(0x44, 0xE5, 0xE5, 0xFF),
    Color(0xE5, 0xE5, 0x44, 0xFF),
    Color(0xE5, 0x44, 0xE5, 0xFF),
    Color(0x44, 0xE5, 0x7A, 0xFF),
    Color(0xE5, 0x44, 0x44, 0xFF),
    Color(0x44, 0x95, 0xE5, 0xFF),
    Color(0xE5, 0x95, 0x44, 0xFF)
};

const Color DARK_COLORS[] = {
    Color(0x28, 0x28, 0x28, 0xFF),
    Color(0x1E, 0x66, 0x66, 0xFF),
    Color(0x66, 0x66, 0x1E, 0xFF),
    Color(0x66, 0x1E, 0x66, 0xFF),
    Color(0x1E, 0x66, 0x36, 0xFF),
    Color(0x66, 0x1E, 0x1E, 0xFF),
    Color(0x1E, 0x42, 0x66, 0xFF),
    Color(0x66, 0x42, 0x1E, 0xFF)
};

#endif // Color_H