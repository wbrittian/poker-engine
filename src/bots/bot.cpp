/*bot.cpp*/

//
// a basic poker bot
//
// William Brittian
// 2025
//

#include "bot.hpp"

Action Bot::getAction(const PublicState& gameState) {
    return Action{Id, BET, 0};
}