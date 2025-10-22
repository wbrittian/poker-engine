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

enum Stage {
    INACTIVE = 0,
    PREFLOP,
    FLOP,
    TURN,
    RIVER,
    SHOWDOWN,
    EVAL
};

class Game {
  private:
    bool Quit = false;

    //
    // general info
    //
    std::vector<Player> players;
    std::vector<Player> playing;

    int SmallBlind = 0;

    Deck Deck;

    int Round = 0;
    bool Active = false;

    //
    // round-specific
    //

    Stage stage = INACTIVE;

    int Pot = 0;
    int Bet = 0;

    std::vector<Card> Cards;

  public:
    //
    // general game state functions
    //
    
};