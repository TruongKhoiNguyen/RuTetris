#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

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

class Game {
public:
    Game();
    void run_game();
    ~Game();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Mix_Music* music;
};

#endif // GAME_H
