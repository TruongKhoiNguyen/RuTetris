#include "App.h"

App::App()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 1) printf("%s\n", SDL_GetError());
}

App::~App()
{
    SDL_Quit();
}

void scan_input() {}

void update_game() {}

void App::run_game() {
    Performer performer;
    //Load and play music
    performer.play_background_music();

    //Test
    state.level = 4;
    state.line_count = 4;
    state.points = 34;

    state.piece.tetromino_index = 1;
    state.piece.rotation = 1;
    state.piece.offset_col = 50;

    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }
        int start_time = SDL_GetTicks();//Framerate cap

        scan_input();
        update_game();
        performer.show(state);

        int end_time = SDL_GetTicks();
        int run_time = end_time - start_time;
        if (run_time < SPF) SDL_Delay(SPF - run_time);
    }
}
