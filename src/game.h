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

using namespace std;

class Game {

private:

    // general info
    Player* User;
    Player* FirstPlayer;
    Deck Deck;

    int NumPlayers;

    // round-specific
    int NumPlaying = 0;

    int Pot = 0;
    int Bet = 0;

public:

    //
    // general game state functions
    //

    // larger scope functions to manage/setup/finish game

    void initializeGame(Player* player, int numBots, int startingCash);
    void finishGame();

    // TODO: this shold begin game functionality
    void newRound();

    // TODO: this should decide winning hand and pay to that player
    void settleRound();


    // utility functions for managing game state

    void addPlayer(Player* player, Player* position);
    void removePlayer(Player* player);
    void rotateOrder();


    //
    // round active functions
    //

    // main game loop
    void runGame();

    // utility functions for managing round

    void dealToPlayer(Player* player);
    // player -> bet if positive, bet -> player if negative
    void settlePlayerBet(int amount, Player* player);
    // player -> pot if positive, pot -> player if negative
    void settlePlayerPot(int amount, Player* player);
    // bet -> pot if positive, pot <- bet if negative
    void settleBetPot(int amount);


    //
    // misc
    //
    Player* getNthPlayer(int N);
    Player* getPreviousPlayer(Player* player);

    //
    // accessors
    //
    int getPot();
    int getBet();

    // shows which player currently has the most cash
    Player* getCurrentLeader();

};