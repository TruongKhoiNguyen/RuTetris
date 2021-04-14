#ifndef PERFORMER_H
#define PERFORMER_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "../Structures.h"

const char TITLE[] = "Tetris";
const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 720;

const int SOUND_FREQUENCY = 44100;
const int CHANNELS = 2;
const int CHUNKSIZE = 2048;
const char BGMUSIC[] = "sound/Soviet_anthem.mp3";

class Performer
{
public:
    Performer();
    ~Performer();
    void play_background_music();
    void show(const Game_State& Game_State) const;
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Mix_Music* music;
};

#endif // PERFORMER_H
