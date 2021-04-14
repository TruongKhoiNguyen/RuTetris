#ifndef STRUCTURES_H
#define STRUCTURES_H

enum class Game_Phase {
    GAME_PHASE_START,
    GAME_PHASE_PLAY,
    GAME_PHASE_LINE,
    GAME_PHASE_GAMEOVER
};

struct Game_State {
    Game_Phase phase;
};


#endif // STRUCTURES_H
