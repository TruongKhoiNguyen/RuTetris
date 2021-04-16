#ifndef TETROMINO_H
#define TETROMINO_H

struct Tetromino {
    const int* shape;
    const int side;

    Tetromino(const int* _shape, int _side): shape(_shape), side(_side) {}
};

const int TETROMINO_1[] = {
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0
};

const int TETROMINO_2[] = {
    2, 2,
    2, 2
};

const int TETROMINO_3[] = {
    0, 0, 0,
    3, 3, 3,
    0, 3, 0
};

const int TETROMINO_4[] = {
    0, 4, 4,
    4, 4, 0,
    0, 0, 0
};

const int TETROMINO_5[] = {
    5, 5, 0,
    0, 5, 5,
    0, 0, 0
};

const int TETROMINO_6[] = {
    6, 0, 0,
    6, 6, 6,
    0, 0, 0
};

const int TETROMINO_7[] = {
    0, 0, 7,
    7, 7, 7,
    0, 0, 0
};

const Tetromino TETROMINOES[] = {
    Tetromino(TETROMINO_1, 4),
    Tetromino(TETROMINO_2, 2),
    Tetromino(TETROMINO_3, 3),
    Tetromino(TETROMINO_4, 3),
    Tetromino(TETROMINO_5, 3),
    Tetromino(TETROMINO_6, 3),
    Tetromino(TETROMINO_7, 3),
};

#endif // TETROMINO_H
