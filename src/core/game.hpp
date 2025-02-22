/*game.h*/

//
// a poker game
//
// William Brittian
// 2025
//

#pragma once

#include <algorithm>
#include <vector>

#include "../deck/deck.hpp"
#include "bot.hpp"
#include "player.hpp"

class Game {
  private:
    bool Quit;

    //
    // general info
    //
    std::shared_ptr<Player> User;
    std::shared_ptr<Player> Head; // TO-DO: rename to "head" or similar
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
    // 5 = settling winner
    int Stage = 0;

    int Pot = 0;
    int Bet = 0;

    std::vector<Card> Cards;

  public:
    //
    // general game state functions
    //

    // larger scope functions to manage/setup/finish game

    void initializeGame(std::shared_ptr<Player> player, int numBots, int startingCash);
    void finishGame();

    // TODO: this should decide winning hand and pay to that player
    void settleRound();

    // utility functions for managing game state

    // adds player after position in the order
    void addPlayer(std::shared_ptr<Player> player, std::shared_ptr<Player> position);
    void removePlayer(std::shared_ptr<Player> player);
    void rotateOrder();

    //
    // round active functions
    //

    // main game loop
    void runGame();

    // round gameplay
    void runRound();

    // loop of betting
    void runBetting();

    // utility functions for managing round

    void dealToPlayer(std::shared_ptr<Player> player);
    void dealCards();

    void settleBet(int amount, std::shared_ptr<Player> player);
    void clearAllBets();

    //
    // misc
    //

    // print statements
    void printState();
    void printScoreboard();
    void printCards();
    void printRoundInfo();
    void printPot();

    //
    // accessors
    //

    std::shared_ptr<Player> getNthPlayer(int n);
    std::shared_ptr<Player> getPreviousPlayer(std::shared_ptr<Player> player);

    int getPot();
    int getBet();
    int getNumPlayers();

    std::shared_ptr<Player> getHead();
};