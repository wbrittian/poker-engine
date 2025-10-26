/*bot.hpp*/

//
// a basic poker bot
//
// William Brittian
// 2025
//

#pragma once

#include <string>

#include "../core/structs.hpp"

class Bot {
private:
    int Id;

public:
    Bot(int pid) : Id(pid) {}

    Action getAction(const PublicState& gameState);
};