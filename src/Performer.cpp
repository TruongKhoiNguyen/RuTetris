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

    if (TTF_Init() != 1) printf("%s", TTF_GetError());
    font = TTF_OpenFont(FONT, 24);
    if (!font) printf("%s", TTF_GetError());
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

void display_text(SDL_Renderer* renderer, TTF_Font* font, const char* text,
                  int x, int y, const Text_Align alignment, const Color& color) {
    SDL_Color sdl_color = SDL_Color{ color.r, color.g, color.b, color.a };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, sdl_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    rect.y = y;
    rect.w = surface->w;
    rect.h = surface->h;

    switch (alignment)
    {
    case Text_Align::TEXT_ALIGN_LEFT:
        rect.x = x;
        break;
    case Text_Align::TEXT_ALIGN_CENTER:
        rect.x = x - surface->w / 2;
        break;
    case Text_Align::TEXT_ALIGN_RIGHT:
        rect.x = x - surface->w;
        break;
    }

    SDL_RenderCopy(renderer, texture, 0, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void display_game_info(SDL_Renderer* renderer, const Game_State& state, TTF_Font* font, const Color& highlight_color) {
    char buffer[4096];

    //Display game information
    snprintf(buffer, sizeof(buffer), "LEVEL: %d", state.level);
    display_text(renderer, font, buffer, 5, 5, Text_Align::TEXT_ALIGN_LEFT, highlight_color);
    snprintf(buffer, sizeof(buffer), "LINES: %d", state.line_count);
    display_text(renderer, font, buffer, 5, 35, Text_Align::TEXT_ALIGN_LEFT, highlight_color);
    snprintf(buffer, sizeof(buffer), "POINTS: %d", state.points);
    display_text(renderer, font, buffer, 5, 65, Text_Align::TEXT_ALIGN_LEFT, highlight_color);
}

/*
Fill play area
*/
void fill_rect(SDL_Renderer* renderer, int x, int y, int width, int height, const Color& color)
{
    SDL_Rect rect = {};
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

/*
Get color
Get edge size for drawing
Draw
    Draw main
    Draw shadow
*/
void draw_cell(SDL_Renderer* renderer, int value, int pos_x, int pos_y, int offset_x, int offset_y) {
    Color base_color = BASE_COLORS[value];
    Color light_color = LIGHT_COLORS[value];
    Color dark_color = DARK_COLORS[value];

    int edge = GRID_SIZE / 8;

    int x = pos_x * GRID_SIZE + offset_x;
    int y = pos_y * GRID_SIZE + offset_y;

    fill_rect(renderer, x, y, GRID_SIZE, GRID_SIZE, dark_color);
    fill_rect(renderer, x + edge, y,
        GRID_SIZE - edge, GRID_SIZE - edge, light_color);
    fill_rect(renderer, x + edge, y + edge,
        GRID_SIZE - edge * 2, GRID_SIZE - edge * 2, base_color);
}

/*
In: Renderer, game_state
Out: Draw board on screen

Draw board background
Draw piece on board
*/
void draw_board(SDL_Renderer* renderer, const int board[], int width, int height,
                int offset_x, int offset_y)
{
    fill_rect(renderer, offset_x, offset_y,
              width * GRID_SIZE, height * GRID_SIZE, BASE_COLORS[0]);

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            draw_cell(renderer, board[i*width + j], i, j, offset_x, offset_y);
        }
    }
}

/*
Display start text on screen
    Calculate text position
    Render text
*/
void show_start_screen(SDL_Renderer* renderer, const Game_State& state, TTF_Font* font, const Color& highlight_color) {
    char buffer[4096];

    int x = WIDTH * GRID_SIZE / 2;
    int y = (HEIGHT * GRID_SIZE + MARGIN_Y) / 2;
    display_text(renderer, font, "PRESS START",
                x, y, Text_Align::TEXT_ALIGN_CENTER, highlight_color);

    snprintf(buffer, sizeof(buffer), "STARTING LEVEL: %d", state.start_level);
    display_text(renderer, font, buffer, x, y + 30, Text_Align::TEXT_ALIGN_CENTER, highlight_color);
}

/*
Get side of piece
For each cell in piece, draw cell
    Get the color of the cell
    Draw cell
*/
void draw_piece(SDL_Renderer* renderer, const Game_State& state) {
    const int side = TETROMINOES[state.piece.tetromino_index].side;
    for (int i = 0; i < side; ++i) {
        for (int j = 0; j < side; ++j) {
            int color_index = state.piece.get_value(i, j);
            if (color_index) {
                draw_cell(renderer, color_index,
                          state.piece.offset_row + i,
                          state.piece.offset_col + j,
                          MARGIN_X, MARGIN_Y);
            }
        }
    }
}

/*

*/
void draw_silhouette(SDL_Renderer* renderer, const Game_State& state) {

}

/*
Draw piece
Draw piece silhouette
*/
void show_play_screen(SDL_Renderer* renderer, const Game_State& state) {
    draw_piece(renderer, state);
    draw_silhouette(renderer, state);
}
void show_line_screen(const Game_State& state) {}
void show_gameover_screen(const Game_State& state) {}

/*
In: Game_State
Out: Output to screen and speaker

Draw back ground
Draw board
Draw information
Draw game
*/
void Performer::show(const Game_State& state) const {
    const Color HIGHLIGHT_COLOR = Color(0xFF, 0xFF, 0xFF, 0xFF);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    draw_board(renderer, state.board, WIDTH, VISIBLE_HEIGHT, MARGIN_X, MARGIN_Y);
    display_game_info(renderer, state, font, HIGHLIGHT_COLOR);

    switch (state.phase) {
    case Game_Phase::GAME_PHASE_START:
        show_start_screen(renderer, state, font, HIGHLIGHT_COLOR);
        break;
    case Game_Phase::GAME_PHASE_PLAY:
        show_play_screen(renderer, state);
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
