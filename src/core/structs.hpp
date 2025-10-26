/*structs.hpp*/

//
// all the relevant enums and structs for engine
//
// William Brittian
// 2025
//

#pragma once

#include <vector>

#include "deck/deck.hpp"

enum Stage {
    INACTIVE = 0,
    PREFLOP,
    FLOP,
    TURN,
    RIVER,
    SHOWDOWN
};

enum ActionTypes {
    NONE = 0, // placeholder for no action
    BET, // used for bet, raise, check, and call
    FOLD // fold hand
};

struct Action {
    int PlayerId;
    enum ActionTypes Type = NONE;
    int Amount = 0;
};

struct Seat {
    int PlayerId;
    bool Active = false;

    int Cash;
    int Bet = 0;
    int PotSplit = 0;
};

struct PublicState {
    std::vector<Seat> Players;
    Stage EngineStage;
    int Current;
    int SmallBlind;
    int Pot;
    int CurrentBet;
    std::vector<Card> Community;
};

struct PlayerState {
    std::vector<Card> Hand;
};

struct EngineSettings {
    int BigBlind = 20;
    int SmallBlind = 10;
    int StartingCash = 1000;
};