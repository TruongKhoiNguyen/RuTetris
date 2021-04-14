#include "Performer.h"

Performer::Performer()
{
    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (!window) printf("%s\n", SDL_GetError());
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) printf("%s\n", SDL_GetError());
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNKSIZE) != 1) printf("%s", Mix_GetError());
}

Performer::~Performer() {
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Performer::play_background_music() {
    Mix_Music* music = Mix_LoadMUS(BGMUSIC);
    Mix_PlayMusic(music, -1);
}

void show_start_screen(const Game_State& state) {}
void show_play_screen(const Game_State& state) {}
void show_line_screen(const Game_State& state) {}
void show_gameover_screen(const Game_State& state) {}

void Performer::show(const Game_State& state) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    switch (state.phase) {
    case Game_Phase::GAME_PHASE_START:
        show_start_screen(state);
        break;
    case Game_Phase::GAME_PHASE_PLAY:
        show_play_screen(state);
        break;
    case Game_Phase::GAME_PHASE_LINE:
        show_line_screen(state);
        break;
    case Game_Phase::GAME_PHASE_GAMEOVER:
        show_gameover_screen(state);
        break;
    }

    SDL_RenderPresent(renderer);
}
