/*bot.h*/

//
// a basic poker bot
//
// William Brittian
// 2025
//

#pragma once

#include <string>

#include "player.h"
#include "action.h"

class Bot : public Player {

private:

    int Level;


public:

    Bot(string name, int startingCash)
        : Player(name, startingCash), Level(5)
        {}
    Bot(string name, int startingCash, int level)
        : Player(name, startingCash), Level(level)
        {}

    // overloaded
    Action getAction(int bet, int pot, int numPlaying);

};