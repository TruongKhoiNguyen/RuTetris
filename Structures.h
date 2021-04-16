#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <cstdint>

#include "Game_Constant.h"
#include "Tetromino.h"

typedef uint8_t u8;

struct Input_State {
    bool quit;

    u8 left;
    u8 right;
    u8 up;
    u8 down;
    u8 a;

    int dleft;
    int dright;
    int dup;
    int ddown;
    int da;

    Input_State():
        quit(false),
        left(0), right(0), up(0), down(0), a(0),
        dleft(0), dright(0), dup(0),
        ddown(0), da(0) {}
};

enum class Game_Phase {
    GAME_PHASE_START,
    GAME_PHASE_PLAY,
    GAME_PHASE_LINE,
    GAME_PHASE_GAMEOVER
};

struct Piece_State {
    int tetromino_index;
    int offset_row;
    int offset_col;
    int rotation;

    int get_value(int row, int col) const {
        int side = TETROMINOES[tetromino_index].side;
        switch (rotation) {
        case 0:
            return TETROMINOES[tetromino_index].shape[row * side + col];
        case 1:
            return TETROMINOES[tetromino_index].shape[(side - col - 1) * side + row];
        case 2:
            return TETROMINOES[tetromino_index].shape[(side - row - 1) * side + (side - col - 1)];
        case 3:
            return TETROMINOES[tetromino_index].shape[col * side + (side - row - 1)];
        }
            return 0;
    }
};

struct Game_State {
    Game_Phase phase;
    int board[WIDTH*HEIGHT];

    int start_level;

    Piece_State piece;

    bool lines[HEIGHT];

    int level;
    int line_count;
    int points;

    bool selecting;
};

enum class Text_Align {
    TEXT_ALIGN_LEFT,
    TEXT_ALIGN_CENTER,
    TEXT_ALIGN_RIGHT
};


#endif // STRUCTURES_H
