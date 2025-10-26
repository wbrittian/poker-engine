/*game.cpp*/

//
// a poker game
//
// William Brittian
// 2025
//

#include "game.hpp"

//
// private functions
//

void Game::advanceGame() {
    GameStage = static_cast<Stage>(GameStage + 1);
    Stage stage = GameStage;

    if (stage == PREFLOP) {
        Round += 1;
        Playing = Players.size();

        int small = SmallBlind;
        int big = getPlayer(1, small);

        resolveBet(small, SmallSize);
        resolveBet(big, BigSize);

        CurrentBet = BigSize;
        Current = getPlayer(2, small);

        return;
    } else if (stage == FLOP) {
        getCurrent();
        Community = TheDeck.drawCards(3);
    } else if (stage == TURN) {
        getCurrent();
        Community.push_back(TheDeck.drawCard());
    } else if (stage == RIVER) {
        getCurrent();
        Community.push_back(TheDeck.drawCard());
    } else if (stage == SHOWDOWN) {
        // figure out best hand
        std::vector<int> bestHands;
        for (int i = 0; i < Players.size(); i++) {
            Seat player = Players[i];

            if (!player.Active) continue;

            Hands[i].evaluateHand(Community);
            if (bestHands.size() == 0) {
                bestHands.push_back(i);
            } else {
                bool better = false;
                Hand myHand = Hands[i];
                for (int j = bestHands.size() - 1; j >= 0; j--) {
                    Hand theirHand = Hands[bestHands[j]];
                    int res = compareHands(myHand, theirHand);

                    if (res == 1) {
                        break;
                    }

                    better = true;
                    if (res == -1) {
                        bestHands.erase(bestHands.begin() + j);
                    }
                }

                if (better) bestHands.push_back(i);
            }
        }

        // pay out winner(s)
        float split = ((float) Pot) / Playing;

        for (int i = 0; i < bestHands.size(); i++) {
            int payout;
            if (i == 0) {
                payout = ceil(split);
            } else {
                payout = floor(split);
            }

            Players[bestHands[i]].Cash += payout;
        }

        // move blinds, reset game state
        Pot = 0;
        TheDeck.refillCards();
        SmallBlind = getPlayer(SmallBlind, 1);

        for (int i = 0; i < Players.size(); i++) {
            Players[i].Active = true;
            Players[i].PotSplit = 0;
            Hands[i].Cards.clear();
        }

        // start next round
        GameStage = INACTIVE;
        advanceGame();
    }

    for (Seat &player : Players) {
        player.Bet = 0;
    }
}


// helper functions
int Game::getPlayer(const int& point, const int& n) {
    return (point + n) % Players.size();
}

void Game::getCurrent() {
    int current;
    Seat currentPlayer = Players[SmallBlind];
    while (!currentPlayer.Active) {
        current = getPlayer(Current, 1);
        currentPlayer = Players[current];
    }
    Current = current;
}

void Game::incCurrent() {
    int current;
    Seat currentPlayer;
    do {
        current = getPlayer(Current, 1);
        currentPlayer = Players[current];
    } while (!currentPlayer.Active);
    Current = current;
}

// necessary??
void Game::getBet(const int& pid, const int& amount) {
    
}

void Game::resolveBet(const int& pid) {
    Seat player = getSeat(pid);
    
    int bet = player.Bet;
    
    player.Bet = 0;
    player.PotSplit += bet;
    Pot += bet;
}

void Game::resolveBet(const int& pid, const int& amount) {
    Seat player = getSeat(pid);

    player.Cash -= amount;
    player.PotSplit += amount;
    Pot += amount;
}

// returns -1 if h1 is better, 0 if tie, 1 if h2
int Game::compareHands(const Hand& h1, const Hand& h2) {
    if (h1.Type > h2.Type) {
        return -1;
    } else if (h1.Type < h2.Type) {
        return 1;
    } else {
        
    }
}

struct Seat& Game::getSeat(const int& pid) {
    // quick jailbreak in case pid = seat number in vector
    int numPlayers = Players.size();
    if (pid < numPlayers && Players[pid].PlayerId == pid) {
        return Players[pid];
    } else {
        for (int i = 0; i < numPlayers; i++) {
            Seat player = Players[i];
            if (player.PlayerId == pid) {
                return player;
            }
        }
    }
}

//
// public functions
//

void Game::initializeGame(const struct EngineSettings& settings, std::vector<int> PlayerIds) {
    TheDeck.refillCards();

    MaxSeats = settings.MaxSeats;
    SmallSize = settings.SmallBlind;
    BigSize = settings.BigBlind;

    for (int id : PlayerIds) {
        struct Seat seat = {
            id,
            true,
            settings.StartingCash,
            0,
            0
        };

        Hand hand;
        hand.PlayerId = id;
        Hands.push_back(hand);
        Players.push_back(seat);
    }

    advanceGame();
}

struct PublicState Game::getPublicState() {
    PublicState state = {
        Players,
        GameStage,
        Current,
        SmallBlind,
        Pot,
        CurrentBet,
        Community
    };

    return state;
}

bool Game::submitAction(const Action& action) {
    int pid = action.PlayerId;
    Stage stage = GameStage;

    if (pid != Current || stage == INACTIVE) {
        return false;
    }

    ActionTypes type = action.Type;
    int amount = action.Amount;
    Seat seat = getSeat(pid);

    // todo: add stages
    if (type == BET) {

    } else if (type == FOLD) {
        Playing--;
        seat.Active = false;

        if (Playing == 1) {

        }
    }


    return true;
}