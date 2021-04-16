#ifndef APP_H
#define APP_H

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

#include "../Structures.h"
#include "Performer.h"

const int FPS = 60;
const int SPF = 1000/60;

class App
{
public:
    App();
    ~App();
    void run_game();
private:
};

#endif // APP_H
