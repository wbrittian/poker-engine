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

#include "structs.hpp"

class Game {
  private:
    bool On = false;

    //
    // general info
    //
    std::vector<Seat> Players;
    Deck Deck;

    //
    // round-specific
    //
    Stage GameStage = INACTIVE;

    int Current = 0;
    int SmallBlind = 0;

    int Pot = 0;
    int CurrentBet = 0;

    std::vector<Card> Community;

  public:
    //
    // general game state functions
    //
    struct PublicState getPublicState();
    bool submitAction(const Action& action);

    void initializeGame(const struct EngineSettings& settings, std::vector<int> PlayerIds);
};