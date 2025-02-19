/*bot.cpp*/

//
// a basic poker bot
//
// William Brittian
// 2025
//

#include "bot.h"

Action Bot::getAction(int bet, int pot, int numPlaying) {
    cout << this->Name << " calls for " << (bet - this->Bet) << endl;
    return {CALL, 0};
}