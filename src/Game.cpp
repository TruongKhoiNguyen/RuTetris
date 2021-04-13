#include "Game.h"

Game::Game() {
    //Initialize libraries
    if (SDL_Init(SDL_INIT_EVERYTHING) != 1) {
        printf("%s", SDL_GetError());
    }

    if (Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNK_SIZE) == -1){
        printf("%s", Mix_GetError());
    }

    //Set up variables

    //SDL2
    window = SDL_CreateWindow(TITLE, WINDOWPOS, WINDOWPOS, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_FLAG);
    if (window == nullptr) {
        printf("%s", SDL_GetError());
    }
    renderer= SDL_CreateRenderer(window, -1, RENDERER_FLAG);
        if (renderer == nullptr) {
        printf("%s", SDL_GetError());
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    //SDL2_mixer
    music = Mix_LoadMUS(MUSIC_PATH);
    if (music == nullptr) {
        printf("%s", Mix_GetError());
    }

}

void Game::run_game() {
    //Start game
    Mix_PlayMusic(music, -1);
    //Game loop
    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                quit = true;
            }
        }
    }

}

Game::~Game() {
    Mix_CloseAudio();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}
