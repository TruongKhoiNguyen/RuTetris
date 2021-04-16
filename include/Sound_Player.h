#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include <iostream>
#include <cstdint>
#include <SDL.h>
#include <SDL_mixer.h>

#include "../Game_Constant.h"

typedef uint32_t u32;

enum class Sound_Effect {
    SELECTION,
    FALL,
    LINE,
    CLEAR,
    GAMEOVER,
    SUCCESS
};

class Sound_Player
{
public:
    Sound_Player();
    ~Sound_Player();
    void play_BG();
    void play_sound_effect(Sound_Effect effect, int loop);
    void pause_BG() const;
    void resume_BG() const;
    void pause_sound_effect() const;
    void resume_sound_effect() const;
    bool is_freeze_time(int time) const;
private:
    Mix_Music* music;

    Mix_Chunk* selection_sound;
    Mix_Chunk* fall_sound;
    Mix_Chunk* line_sound;
    Mix_Chunk* clear_sound;
    Mix_Chunk* gameover_sound;
    Mix_Chunk* success_sound;

    u32 last_time;
};

#endif // SOUND_PLAYER_H
