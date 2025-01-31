/*bot.h*/

//
// a basic poker bot
//
// William Brittian
// 2025
//

#pragma once

#include "player.h"

class Bot : public Player {

private:

    int Level;


public:

    Bot(int startingCash)
        : Player(startingCash), Level(5)
        {}
    Bot(int startingCash, int level)
        : Player(startingCash), Level(level)
        {}
    


};