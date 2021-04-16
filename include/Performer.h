#ifndef PERFORMER_H
#define PERFORMER_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "../Game_Constant.h"
#include "../Structures.h"
#include "../Color.h"
#include "Sound_Player.h"

class Performer
{
public:
    Performer();
    ~Performer();
    void play_background_music();
    void show(const Game_State& Game_State) ;
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    Sound_Player player;
};

#endif // PERFORMER_H
