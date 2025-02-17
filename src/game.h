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
    //
    // general info
    //
    shared_ptr<Player> User;
    shared_ptr<Player> FirstPlayer;
    Deck Deck;

    int NumPlayers = 0;
    int Round = 0;

    bool Active = false;

    //
    // round-specific
    //
    int NumPlaying = 0;

    // 0 = pre-deal (10 to play)
    // 1 = pre-flop
    // 2 = post flop
    // 3 = river 1
    // 4 = river 2
    int Stage = 0;

    int Pot = 0;
    int Bet = 0;

    vector<Card> Cards;

public:

    //
    // general game state functions
    //

    // larger scope functions to manage/setup/finish game

    void initializeGame(shared_ptr<Player> player, int numBots, int startingCash);
    void finishGame();

    // TODO: this shold begin game functionality
    void startRound();

    // TODO: this should decide winning hand and pay to that player
    void settleRound();


    // utility functions for managing game state

    // adds player after position in the order
    void addPlayer(shared_ptr<Player> player, shared_ptr<Player> position);
    void removePlayer(shared_ptr<Player> player);
    void rotateOrder();


    //
    // round active functions
    //

    // main game loop
    void runGame();

    void runBetting();

    // utility functions for managing round

    // TO-DO: refactor some of these
    void dealToPlayer(shared_ptr<Player> player);
    // player -> bet if positive, bet -> player if negative
    void settlePlayerBet(int amount, shared_ptr<Player> player);
    // player -> pot if positive, pot -> player if negative
    void settlePlayerPot(int amount, shared_ptr<Player> player);
    // bet -> pot if positive, pot <- bet if negative
    void settleBetPot(int amount);

    void settleBet(int amount, shared_ptr<Player> player);
    void clearAllBets();

    void printState();
    void printScoreboard();


    //
    // misc
    //
    shared_ptr<Player> getNthPlayer(int N);
    shared_ptr<Player> getPreviousPlayer(shared_ptr<Player> player);
    void printCards();
    void printRoundInfo();

    //
    // accessors
    //
    int getPot();
    int getBet();
    int getNumPlayers();

    shared_ptr<Player> getFirstPlayer();

    // shows which player currently has the most cash
    shared_ptr<Player> getCurrentLeader();

};