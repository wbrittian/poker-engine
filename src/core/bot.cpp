/*bot.cpp*/

//
// a basic poker bot
//
// William Brittian
// 2025
//

#include "bot.hpp"

Action Bot::getAction(int bet, int pot, int numPlaying) {
    std::cout << this->Name << " calls for " << (bet - this->Bet) << std::endl;
    return {CALL, 0};
}