#include <iostream>
#include <SDl.h>
#include <SDL_mixer.h>

int main(int argc, char* argv[]) {
    //Game constants

    //Display
    const char TITLE[] = "Tetris";
    const int SCREEN_WIDTH = 300;
    const int SCREEN_HEIGHT = 720;
    const int WINDOW_FLAG = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    const int WINDOWPOS = SDL_WINDOWPOS_UNDEFINED;
    const int RENDERER_FLAG = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    //Music
    const int FREQUENCY = 44100;
    const int CHANNELS = 2;
    const int CHUNK_SIZE = 2048;

    const char MUSIC_PATH[] = "sound/Soviet_anthem.mp3";

    //Initialize libraries
    if (SDL_Init(SDL_INIT_EVERYTHING) != 1) {
        printf("%s", SDL_GetError());
    }

    if (Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNK_SIZE) == -1){
        printf("%s", Mix_GetError());
    }

    //Set up variables

    //SDL2
    SDL_Window* window = SDL_CreateWindow(TITLE, WINDOWPOS, WINDOWPOS, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_FLAG);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, RENDERER_FLAG);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    //SDL2_mixer
    Mix_Music* music = Mix_LoadMUS(MUSIC_PATH);
    if (music == nullptr) {
        printf("%s", Mix_GetError());
    }
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

    //Delete objects
    Mix_CloseAudio();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
