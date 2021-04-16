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

/*
Load music
Declare test
Run game loop
    Get input
    Update game
    Render and Play sound
*/
void App::run_game() {
    Performer performer;
    //Load and play music
    performer.play_background_music();

    //Create game state
    Game_State state;
    std::fill(state.board, state.board + WIDTH*HEIGHT, 0);

    //Test
    state.phase = Game_Phase::GAME_PHASE_LINE;
    state.start_level = 10;

    state.level = 4;
    state.line_count = 4;
    state.points = 34;

    state.piece.tetromino_index = 3;
    state.piece.rotation = 2;
    state.piece.offset_col = 0;
    state.piece.offset_row = 2;

    std::fill(state.lines, state.lines + HEIGHT, false);
    state.lines[20] = true;

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            printf("%d ",state.board[i*WIDTH + j]);
        }
        printf("\n");
    }

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
