#include "Logic.h"

//Get random number from 0 to the number of TETROMINOES
inline int generate_piece() {
    return rand() % TETROMINOES_SIZE;
}

/*
Generate QUEUE_SIZE items for display
*/
Logic::Logic()
{
    srand(time(nullptr));

    for (int i = 0; i < QUEUE_SIZE; ++i) {
        piece_queue.push(generate_piece());
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
inline void update_game_play(const Input_State& input, Game_State& state, std::queue<int>& Piece_queue) {}
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
    default:
        break;
    }
}
