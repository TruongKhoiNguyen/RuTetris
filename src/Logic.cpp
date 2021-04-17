#include "Logic.h"
/*
Generate QUEUE_SIZE items for display
*/
Logic::Logic()
{
    srand(time(nullptr));

    for (int i = 0; i < QUEUE_SIZE; ++i) {
        piece_queue.push(rand() % TETROMINOES_SIZE);
    }
}

/*
Choose start level
    Check input
    Play sound
Reset game state
*/
inline void update_game_start(const Input_State& input, Game_State& state) {
    if (input.dup > 0)
    {
        ++state.start_level;
        state.selecting = true;
    }
    else if (input.ddown > 0 && state.start_level > 0)
    {
        --state.start_level;
        state.selecting = true;
    }
    else if (input.da > 0)
    {
        memset(state.board, 0, WIDTH * HEIGHT * sizeof(int));
        state.level = state.start_level;
        state.line_count = 0;
        state.points = 0;
        state.phase = Game_Phase::GAME_PHASE_PLAY;
        state.selecting = true;
    }
    else state.selecting = false;
}

bool check_piece_valid(int board[], const Piece_State& piece){
    int side = TETROMINOES[piece.tetromino_index].side;

    for (int row = 0; row < side; ++row)
        for (int col = 0; col < side; ++col)
            if (piece.get_value(row, col))
            {
                int board_row = piece.offset_row + row;
                int board_col = piece.offset_col + col;
                bool condition = (board_row < 0) | (board_row >= HEIGHT) |
                                 (board_col < 0) | (board_col >= WIDTH) |
                                 board[row * WIDTH + col];
                if (condition) return false;
            }
    return true;
}

/*
Create new piece
Move
Check collision
    Update
*/
inline void move_piece(const Input_State& input, Game_State& state){
    Piece_State piece = state.piece;
    if (input.dleft >0) --piece.offset_col;
    if (input.dright > 0) ++piece.offset_col;
    if (input.dup > 0) piece.rotation = (piece.rotation + 1) % 4;

    if (check_piece_valid(state.board, piece))
        state.piece = piece;
}

inline void hard_drop(Game_State& state, std::queue<int>& piece_queue){}
void soft_drop(Game_State& state) {}
inline void check_line(Game_State& state) {}
inline void check_game_over(Game_State& state) {}

/*
Change piece position and rotation
Check hard drop
    Hard drop
Soft drop
Check line
Check game over
*/
inline void update_game_play(const Input_State& input, Game_State& state, std::queue<int>& piece_queue) {
    move_piece(input, state);
    if (input.da > 0) hard_drop(state, piece_queue);
    soft_drop(state);
    check_line(state);
    check_game_over(state);
}
inline void update_game_line(Game_State& state){};
inline void update_game_gameover(const Input_State& input, Game_State& state) {}

/*
Check if quit
Check game_phase
*/
void Logic::update_game(const Input_State& input, Game_State& state, bool& quit) {
    quit = quit | input.quit;

    switch(state.phase){
    case Game_Phase::GAME_PHASE_START:
        update_game_start(input, state);
        break;
    case Game_Phase::GAME_PHASE_PLAY:
        update_game_play(input, state, piece_queue);
        break;
    case Game_Phase::GAME_PHASE_LINE:
        update_game_line(state);
        break;
    case Game_Phase::GAME_PHASE_GAMEOVER:
        update_game_gameover(input, state);
        break;
    }
}
