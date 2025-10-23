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
#include "hand.hpp"

class Game {
  private:
    bool On = false;

    //
    // general info
    //
    std::vector<Seat> Players;
    std::vector<Hand> Hands;
    Deck TheDeck;

    int Round = 0;
    int MaxSeats;

    //
    // round-specific
    //
    Stage GameStage = INACTIVE;

    int Current = 0;
    int SmallBlind = 0;

    int Playing;

    int SmallSize;
    int BigSize;

    int Pot = 0;
    int CurrentBet = 0;

    std::vector<Card> Community;

    // game helpers
    void advanceGame();

    // small helpers
    int getPlayer(const int& n, const int& pointer);
    void getCurrent();
    void incCurrent();
    void getBet(const int& pid, const int& amount);
    void resolveBet(const int& pid);
    void resolveBet(const int& pid, const int& amount);

    struct Seat getSeat(const int& pid);

  public:
    void initializeGame(const struct EngineSettings& settings, std::vector<int> PlayerIds);

    struct PublicState getPublicState();
    bool submitAction(const Action& action);

};