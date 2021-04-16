#include "Sound_Player.h"

/*
Check init status of SDL
    if not init
        init
Init SDL_Mixer
Load sound
*/
Sound_Player::Sound_Player():last_time(0)
{
    if (!SDL_WasInit(SDL_INIT_EVERYTHING)) {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            printf("%s", SDL_GetError());
        }
    }

    if (Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNKSIZE) != 1) printf("%s", Mix_GetError());

    selection_sound = Mix_LoadWAV(SELECTION_SOUND);
    if (!selection_sound) printf("%s", Mix_GetError());
    fall_sound = Mix_LoadWAV(FALL_SOUND);
    if (!fall_sound) printf("%s", Mix_GetError());
    line_sound = Mix_LoadWAV(LINE_SOUND);
    if (!line_sound) printf("%s", Mix_GetError());
    clear_sound = Mix_LoadWAV(CLEAR_SOUND);
    if (!clear_sound) printf("%s", Mix_GetError());
    gameover_sound = Mix_LoadWAV(GAMEOVER_SOUND);
    if (!gameover_sound) printf("%s", Mix_GetError());
    success_sound = Mix_LoadWAV(SUCCESS_SOUND);
    if (!success_sound) printf("%s", Mix_GetError());
}

Sound_Player::~Sound_Player()
{
    Mix_CloseAudio();

    Mix_FreeMusic(music);

    Mix_FreeChunk(selection_sound);
    Mix_FreeChunk(fall_sound);
    Mix_FreeChunk(line_sound);
    Mix_FreeChunk(clear_sound);
    Mix_FreeChunk(gameover_sound);
    Mix_FreeChunk(success_sound);

    Mix_Quit();
}

void Sound_Player::play_BG() {
    music = Mix_LoadMUS(BGMUSIC);
    Mix_PlayMusic(music, -1);
}

/*
Check sound effect
Play sound effect
Update time
*/
void Sound_Player::play_sound_effect(Sound_Effect effect, int loop) {
    switch (effect) {
    case Sound_Effect::SELECTION:
        Mix_PlayChannel(-1, selection_sound, loop);
        break;
    case Sound_Effect::FALL:
        Mix_PlayChannel(-1, fall_sound, loop);
        break;
    case Sound_Effect::LINE:
        Mix_PlayChannel(-1, line_sound, loop);
        break;
    case Sound_Effect::CLEAR:
        Mix_PlayChannel(-1, clear_sound, loop);
        break;
    case Sound_Effect::GAMEOVER:
        Mix_PlayChannel(-1, gameover_sound, loop);
        break;
    case Sound_Effect::SUCCESS:
        Mix_PlayChannel(-1, success_sound, loop);
        break;
    }

    last_time = SDL_GetTicks();
}

void Sound_Player::pause_BG() const {
    Mix_PauseMusic();
}

void Sound_Player::resume_BG() const {
    Mix_ResumeMusic();
}

void Sound_Player::pause_sound_effect() const {
    Mix_Pause(-1);
}

void Sound_Player::resume_sound_effect() const {
    Mix_Resume(-1);
}

bool Sound_Player::is_freeze_time(int time) const {
    return (SDL_GetTicks() - last_time) < (u32)time;
}
