#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdint>

#include "../Game_Constant.h"
#include "../Structures.h"
#include "../Tetromino.h"
#include "../Logic_Constant.h"

typedef uint32_t u32;

class Logic
{
public:
    Logic();
    void update_game(const Input_State& input, Game_State& state, bool& quit, const u32 _time);
private:
    std::queue<int> piece_queue;
    double this_time;
    double next_drop_time;
};

#endif // LOGIC_H
