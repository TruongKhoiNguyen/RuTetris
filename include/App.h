#ifndef APP_H
#define APP_H

#include <iostream>
#include <cstdint>
#include <SDL.h>
#include <SDL_mixer.h>

#include "../Structures.h"
#include "Logic.h"
#include "Performer.h"

typedef uint8_t u8;
typedef uint32_t u32;

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
