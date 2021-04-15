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

    int level;
    int line_count;
    int points;
};

enum class Text_Align {
    TEXT_ALIGN_LEFT,
    TEXT_ALIGN_CENTER,
    TEXT_ALIGN_RIGHT
};


#endif // STRUCTURES_H
