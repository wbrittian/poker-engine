/*engine.cpp*/

//
// a poker engine
//
// William Brittian
// 2025
//

#include "engine.hpp"

//
// private functions
//

void PokerEngine::advanceEngine() {
    EngineStage = static_cast<Stage>(EngineStage + 1);
    Stage stage = EngineStage;

    if (stage == PREFLOP) {
        beginRound();
        return;
    } else if (stage == FLOP) {
        getCurrent();
        LastAction = getLast(Current);
        Community = TheDeck.drawCards(3);
    } else if (stage == TURN) {
        getCurrent();
        LastAction = getLast(Current);
        Community.push_back(TheDeck.drawCard());
    } else if (stage == RIVER) {
        getCurrent();
        LastAction = getLast(Current);
        Community.push_back(TheDeck.drawCard());
    } else if (stage == SHOWDOWN) {
        resolveShowdown();
        advanceEngine();
        return;
    }

    for (Seat& player : Players) {
        player.Bet = 0;
    }
}

void PokerEngine::beginRound() {
    for (int i = 0; i < Players.size(); i++) {
        Players[i].Bet = 0;
        Hands[i].Cards = TheDeck.drawCards(2);
    }

    Round += 1;
    Playing = Players.size();

    int small = SmallBlind;
    int big = getPlayer(1, small);

    addBet(small, SmallSize);
    addBet(big, BigSize);

    CurrentBet = BigSize;
    Current = getPlayer(2, small);
    LastAction = big;
}

void PokerEngine::resolveBetting() {
    for (Seat& player : Players) {
        resolveBet(player);
    }

    CurrentBet = 0;
}

void PokerEngine::resolveShowdown() {
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
    // TODO: add sidepot management
    float split = ((float) Pot) / bestHands.size();

    for (int i = 0; i < bestHands.size(); i++) {
        int payout;
        if (i == 0) {
            payout = ceil(split);
        } else {
            payout = floor(split);
        }

        Players[bestHands[i]].Cash += payout;
    }

    resetRound();
}

void PokerEngine::resolveFold() {
    resolveBetting();

    for (Seat& player : Players) {
        if (player.Active) {
            player.Cash += Pot;
            break;
        }
    }

    resetRound();
}

void PokerEngine::resetRound() {
    // move blinds, reset engine state
    Pot = 0;
    TheDeck.refillCards();
    SmallBlind = getPlayer(SmallBlind, 1);

    for (int i = 0; i < Players.size(); i++) {
        Players[i].Active = true;
        Players[i].PotSplit = 0;
        Hands[i].Cards.clear();
    }

    AllIn = false;
    EngineStage = INACTIVE;
}


// helper functions
int PokerEngine::getPlayer(const int& point, const int& n) {
    int size = static_cast<int>(Players.size());
    int res = (point + n) % size;
    if (res < 0) res += size;
    return res;
}

void PokerEngine::getCurrent() {
    int current = SmallBlind;
    Seat currentPlayer = Players[current];
    while (!currentPlayer.Active) {
        current = getPlayer(current, 1);
        currentPlayer = Players[current];
    }
    Current = current;
}

void PokerEngine::incCurrent() {
    int current = Current;
    Seat currentPlayer;
    do {
        current = getPlayer(current, 1);
        currentPlayer = Players[current];
    } while (!currentPlayer.Active);
    Current = current;
}

int PokerEngine::getLast(const int& raiser) {
    int current = raiser;
    Seat currentPlayer;
    do {
        current = getPlayer(current, -1);
        currentPlayer = Players[current];
    } while (!currentPlayer.Active);
    return current;
}

void PokerEngine::resolveBet(Seat& player) {
    int bet = player.Bet;
    
    player.Bet = 0;
    player.PotSplit += bet;
    Pot += bet;
}

void PokerEngine::resolveBet(const int& pid, const int& amount) {
    Seat& player = getSeat(pid);

    player.Cash -= amount;
    player.PotSplit += amount;
    Pot += amount;
}

void PokerEngine::addBet(const int& pid, const int& amount) {
    Seat& player = getSeat(pid);

    int diff = amount - player.Bet;
    player.Cash -= diff;
    player.Bet = amount;
}

// returns -1 if h1 is better, 0 if tie, 1 if h2 is better
int PokerEngine::compareHands(const Hand& h1, const Hand& h2) {
    if (h1.Type > h2.Type) {
        return -1;
    } else if (h1.Type < h2.Type) {
        return 1;
    } else {
        if (h1.HandHigh > h2.HandHigh) return -1;
        if (h1.HandHigh < h2.HandHigh) return 1;
        if (h1.OtherHigh > h2.OtherHigh) return -1;
        if (h1.OtherHigh < h2.OtherHigh) return 1;
        return 0;
    }
}

Seat& PokerEngine::getSeat(const int& pid) {
    int numPlayers = Players.size();
    if (pid < numPlayers && Players[pid].PlayerId == pid) {
        return Players[pid];
    }
    for (int i = 0; i < numPlayers; i++) {
        if (Players[i].PlayerId == pid) {
            return Players[i];
        }
    }
    return Players[0];
}

int PokerEngine::getIdx(const int& pid) {
    for (int i = 0; i < Players.size(); i++) {
        if (Players[i].PlayerId == pid) {
            return i;
        }
    }
    return -1;
}

//
// public functions
//

void PokerEngine::initializeEngine(const  EngineSettings& settings, const int& numPlayers) {
    TheDeck.refillCards();

    SmallSize = settings.SmallBlind;
    BigSize = settings.BigBlind;

    for (int id = 0; id < numPlayers; id++) {
        Seat seat = {
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

    advanceEngine();
}

PublicState PokerEngine::getPublicState() {
    return PublicState{
        Round,
        Players,
        EngineStage,
        Current,
        SmallBlind,
        Pot,
        CurrentBet,
        Community
    };
}

PlayerState PokerEngine::getPlayerState(const int& pid) {
    return PlayerState{
        Hands[pid].Cards
    };
}

bool PokerEngine::submitAction(const Action& action) {
    int pid = action.PlayerId;
    Stage stage = EngineStage;

    if (pid != Current || stage == INACTIVE) {
        return false;
    }

    ActionTypes type = action.Type;
    Seat& seat = getSeat(pid);

    if (type == BET) {
        int amount = action.Amount;
        int bet;

        if (amount == 0) {
            bet = CurrentBet;
        } else if (amount >= seat.Cash) {
            bet = seat.Cash;
            LastAction = getLast(pid);
            AllIn = true;
        } else if (amount < std::max(2 * CurrentBet, BigSize)) {
            return false;
        } else {
            bet = amount;
            LastAction = getLast(pid);
        }
        
        addBet(pid, bet);
        CurrentBet = bet;
    } else if (type == FOLD) {
        Playing--;
        seat.Active = false;

        if (Playing == 1) {
            resolveFold();
            return true;
        }
    } else if (type == NONE) {
        return false;
    }

    if (Current == LastAction) {
        resolveBetting();
        advanceEngine();
    } else {
        incCurrent();
    }

    return true;
}