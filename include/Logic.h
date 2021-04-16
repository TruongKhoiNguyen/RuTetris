#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "../Game_Constant.h"
#include "../Structures.h"
#include "../Tetromino.h"
#include "../Logic_Constant.h"

class Logic
{
public:
    Logic();
    void update_game(const Input_State& input, Game_State& state, bool& quit);
private:
    std::queue<int> piece_queue;
};

#endif // LOGIC_H
