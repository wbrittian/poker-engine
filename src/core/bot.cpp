/*bot.cpp*/

//
// a basic poker bot
//
// William Brittian
// 2025
//

#include "bot.hpp"

Action Bot::getAction(int bet, int pot, int numPlaying) {
    setColor("purple");
    std::cout << this->Name << " calls for " << (bet - this->Bet) << std::endl;
    setColor("black");
    return {BET, 0};
}