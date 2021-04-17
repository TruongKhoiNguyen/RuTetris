#include "Performer.h"

Performer::Performer()
{
    if (!SDL_WasInit(SDL_INIT_EVERYTHING))
        if (SDL_Init(SDL_INIT_EVERYTHING) != 1) printf("%s", SDL_GetError());
    //Create window and renderer
    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (!window) printf("%s\n", SDL_GetError());
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) printf("%s\n", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    //Initiate libraries
    if (TTF_Init() != 1) printf("%s", TTF_GetError());
    font = TTF_OpenFont(FONT, 24);
    if (!font) printf("%s", TTF_GetError());
}

Performer::~Performer() {
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Performer::play_background_music() {
    player.play_BG();
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
    fill_rect(renderer, x + edge, y, GRID_SIZE - edge, GRID_SIZE - edge, light_color);
    fill_rect(renderer, x + edge, y + edge, GRID_SIZE - edge * 2, GRID_SIZE - edge * 2, base_color);
}

/*
In: Renderer, game_state
Out: Draw board on screen

Draw board background
Draw piece on board
Omit 2 first row
*/
void draw_board(SDL_Renderer* renderer, const int board[], int width, int height,
                int offset_x, int offset_y)
{
    fill_rect(renderer, offset_x, offset_y,
              width * GRID_SIZE, height * GRID_SIZE, BASE_COLORS[0]);

    for (int row = 0; row < height; ++row)
        for (int col = 0; col < height; ++col)
            draw_cell(renderer, board[row*width + col], col, row, offset_x, offset_y);

    fill_rect(renderer, 0, MARGIN_Y,
              WIDTH * GRID_SIZE, (HEIGHT - VISIBLE_HEIGHT) * GRID_SIZE,
              Color(0x00, 0x00, 0x00, 0x00));
}

/*
Display start text on screen
    Calculate text position
    Render text
    Play sound if selecting
*/
inline void show_start_screen(SDL_Renderer* renderer, const Game_State& state, TTF_Font* font, const Color& highlight_color,
                              Sound_Player& player) {
    char buffer[4096];
    int x = WIDTH * GRID_SIZE / 2;
    int y = (HEIGHT * GRID_SIZE + MARGIN_Y) / 2;

    display_text(renderer, font, "PRESS START",
                x, y, Text_Align::TEXT_ALIGN_CENTER, highlight_color);
    snprintf(buffer, sizeof(buffer), "STARTING LEVEL: %d", state.start_level);
    display_text(renderer, font, buffer, x, y + 30, Text_Align::TEXT_ALIGN_CENTER, highlight_color);

    if (state.selecting)
        player.play_sound_effect(Sound_Effect::SELECTION, 0);
}

void draw_rect(SDL_Renderer* renderer, int x, int y, int width, int height, const Color& color){
    SDL_Rect rect = {};
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, &rect);
}

/*
Calculate position
Draw rect
*/
void draw_outline(SDL_Renderer* renderer, int value, int pos_x, int pos_y, int offset_x, int offset_y) {
    Color base_color = BASE_COLORS[value];
    int x = pos_x * GRID_SIZE + offset_x;
    int y = pos_y * GRID_SIZE + offset_y;
    draw_rect(renderer, x, y, GRID_SIZE, GRID_SIZE, base_color);
}

/*
Get side of piece
For each cell in piece, draw cell
    Get the color of the cell
    Draw cell
*/
void draw_piece(SDL_Renderer* renderer, const Piece_State& piece, bool outline = false) {
    const int side = TETROMINOES[piece.tetromino_index].side;
    for (int row = 0; row < side; ++row)
        for (int col = 0; col < side; ++col)
        {
           int color_index = piece.get_value(row, col);
           if (color_index)
           {
                if (!outline)
                    draw_cell(renderer, color_index,
                          piece.offset_col + col,
                          piece.offset_row + row,
                          MARGIN_X, MARGIN_Y);
                else
                    draw_outline(renderer, color_index,
                                 piece.offset_col + col,
                                 piece.offset_row + row,
                                 MARGIN_X, MARGIN_Y);
           }
        }
}

/*
For each piece check if it collide with wall or other piece
    Get each piece
    Check position
        Check out of bounce
        Collision with other piece
    Return
*/
inline bool detect_collision(const int board[], const Piece_State& piece) {
    int side = TETROMINOES[piece.tetromino_index].side;
    for (int row = 0; row < side; ++row)
        for (int col = 0; col < side; ++col)
            if (piece.get_value(row, col)) {
                int board_row = piece.offset_row + row;
                int board_col = piece.offset_col + col;
                bool condition = (board_row < 0) | (board_row >= HEIGHT) |
                                 (board_col < 0) | (board_col >= WIDTH) |
                                 board[board_row * WIDTH + board_col];
                if (condition) return true;
            }
    return false;
}

/*
Push down piece
    Push down
    Detect collision
    Reposition
Draw piece
*/
inline void draw_silhouette(SDL_Renderer* renderer, const Game_State& state) {
    Piece_State piece = state.piece;

    while (!detect_collision(state.board, piece))
        ++piece.offset_row;
    --piece.offset_row;

    draw_piece(renderer, piece, true);
}

/*
Draw piece
Draw piece silhouette
Play fall sound
    check last sound time
    if last sound time > define time
        Play sound
*/
inline void show_play_screen(SDL_Renderer* renderer, const Game_State& state,
                             Sound_Player& player) {
    draw_piece(renderer, state.piece);
    draw_silhouette(renderer, state);

    if (!player.is_freeze_time(1000))
        player.play_sound_effect(Sound_Effect::FALL, 0);
}

/*
Check filled row
Flash filled area
Play sound
    check last sound time
    if last sound time > define time
    Play sound
*/
void show_line_screen(SDL_Renderer* renderer, const Game_State& state, const Color& highlight_color,
                      Sound_Player& player) {
    for (int i = HEIGHT-1; i >= 0; --i)
        if (state.lines[i]){
            int x = 0;
            int y = i * GRID_SIZE + MARGIN_Y;
            fill_rect(renderer, x, y, WIDTH * GRID_SIZE, GRID_SIZE, highlight_color);

            if (!player.is_freeze_time(1000))
                player.play_sound_effect(Sound_Effect::LINE, 0);
        }
}
void show_gameover_screen(const Game_State& state) {}

/*
In: Game_State
Out: Output to screen and speaker

Draw back ground
Draw board
Draw information
Draw game
*/
void Performer::show(const Game_State& state) {
    const Color HIGHLIGHT_COLOR = Color(0xFF, 0xFF, 0xFF, 0xFF);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    draw_board(renderer, state.board, WIDTH, HEIGHT, MARGIN_X, MARGIN_Y);
    display_game_info(renderer, state, font, HIGHLIGHT_COLOR);

    switch (state.phase) {
    case Game_Phase::GAME_PHASE_START:
        show_start_screen(renderer, state, font, HIGHLIGHT_COLOR, player);
        break;
    case Game_Phase::GAME_PHASE_PLAY:
        show_play_screen(renderer, state, player);
        break;
    case Game_Phase::GAME_PHASE_LINE:
        show_line_screen(renderer, state, HIGHLIGHT_COLOR, player);
        break;
    case Game_Phase::GAME_PHASE_GAMEOVER:
        show_gameover_screen(state);
        break;
    default:
        break;
    }

    SDL_RenderPresent(renderer);
}
