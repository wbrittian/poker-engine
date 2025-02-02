/*game.h*/

//
// a poker game
//
// William Brittian
// 2025
//

#pragma once

#include <vector>
#include <algorithm>

#include "player.h"
#include "bot.h"
#include "deck.h"
#include "member.h"

using namespace std;

class Game {

private:

    // general info
    vector<Member> Members;
    Deck Deck;

    Member* BigBlind;
    Member* SmallBlind;

    // round-specific
    int NumPlaying;

    int Pot;
    vector<int> PotSplits;

    int Bet;
    vector<int> BetSplits;

    bool RoundActive;

public:

    //
    // general game state functions
    //

    // larger scope functions to manage/setup game

    void initializeGame(Player& player, int numBots, int startingCash);
    void newRound();

    // TODO: this should decide winning hand and pay to that player
    void settleRound();

    // utility functions for managing game state

    void addPlayer(Player player);
    void removePlayer(Player* player);
    void moveBlinds();


    //
    // round active functions
    //

    // utility functions for managing round

    void dealToPlayer(Player& player);
    // player -> bet if positive, bet -> player if negative
    void settlePlayerBet(int amount, Player& player);
    // player -> pot if positive, pot -> player if negative
    void settlePlayerPot(int amount, Player& player);
    // bet -> pot if positive, pot <- bet if negative
    void settleBetPot(int amount);


    //
    // misc
    //
    int findPlayerIndex(Player* player);

    //
    // accessors
    //
    int getPot();
    int getBet();

    // shows which player currently has the most cash
    Player* getCurrentLeader();

};