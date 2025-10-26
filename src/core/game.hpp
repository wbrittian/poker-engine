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

    //
    // round-specific
    //
    Stage GameStage = INACTIVE;

    int Current = 0;
    int SmallBlind = 0;
    int Raiser;
    bool AllIn = false;

    int Playing;

    int SmallSize;
    int BigSize;

    int Pot = 0;
    int CurrentBet = 0;

    std::vector<Card> Community;

    // game helpers
    void advanceGame();
    void beginRound();
    void resolveBetting();
    void resolveFold();
    void resolveShowdown();
    void resetRound();

    // other helpers
    int getPlayer(const int& n, const int& pointer);
    void getCurrent();
    void incCurrent();
    void getBet(const int& pid, const int& amount);
    void resolveBet(Seat& player);
    void resolveBet(const int& pid, const int& amount);
    int compareHands(const Hand& h1, const Hand& h2);
    Seat& getSeat(const int& pid);
    int getIdx(const int& pid);

  public:
    void initializeGame(const EngineSettings& settings, std::vector<int> PlayerIds);

    PublicState getPublicState();
    bool submitAction(const Action& action);

};