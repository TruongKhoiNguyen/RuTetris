#ifndef LOGIC_CONSTANT_H
#define LOGIC_CONSTANT_H

#include "Game_Constant.h"

const int TETROMINOES_SIZE = sizeof(TETROMINOES)/sizeof(TETROMINOES[0]);

const int FRAMES_PER_DROP[] = {
    48,
    43,
    38,
    33,
    28,
    23,
    18,
    13,
    8,
    6,
    5,
    5,
    5,
    4,
    4,
    4,
    3,
    3,
    3,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    1
};

const double TARGET_SECONDS_PER_FRAME = 1.f / 60.f;

#endif // LOGIC_CONSTANT_H
