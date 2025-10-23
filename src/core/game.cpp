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
    this->GameStage = static_cast<Stage>(this->GameStage + 1);
    Stage stage = this->GameStage;

    if (stage == PREFLOP) {
        this->Round += 1;
        this->Playing = this->Players.size();

        int small = this->SmallBlind;
        int big = getPlayer(1, small);

        this->resolveBet(small, this->SmallSize);
        this->resolveBet(big, this->BigSize);

        this->CurrentBet = this->BigSize;
        this->Current = this->getPlayer(2, small);

        return;
    } else if (stage == FLOP) {
        this->getCurrent();
        this->Community = this->TheDeck.drawCards(3);
    } else if (stage == TURN) {
        this->getCurrent();
        this->Community.push_back(this->TheDeck.drawCard());
    } else if (stage == RIVER) {
        this->getCurrent();
        this->Community.push_back(this->TheDeck.drawCard());
    } else if (stage == SHOWDOWN) {
        // figure out best hand
        

        // pay out winner(s)
        std::vector<int> winners;
        float split = ((float) this->Pot) / this->Playing;

        for (int i = 0; i < winners.size(); i++) {
            int payout;
            if (i == 0) {
                payout = ceil(split);
            } else {
                payout = floor(split);
            }

            this->Players[winners[i]].Cash += payout;
        }

        // move blinds, reset game state
        this->Pot = 0;
        this->TheDeck.refillCards();
        this->SmallBlind = this->getPlayer(this->SmallBlind, 1);

        for (int i = 0; i < this->Players.size(); i++) {
            this->Players[i].Active = true;
            this->Players[i].PotSplit = 0;
            this->Hands[i].Cards.clear();
        }

        // start next round
        this->GameStage = INACTIVE;
        this->advanceGame();
    }

    for (Seat &player : this->Players) {
        player.Bet = 0;
    }
}


// helper functions
int Game::getPlayer(const int& point, const int& n) {
    return (point + n) % this->Players.size();
}

void Game::getCurrent() {
    int current;
    Seat currentPlayer = this->Players[this->SmallBlind];
    while (!currentPlayer.Active) {
        current = this->getPlayer(this->Current, 1);
        currentPlayer = this->Players[current];
    }
    this->Current = current;
}

void Game::incCurrent() {
    int current;
    Seat currentPlayer;
    do {
        current = this->getPlayer(this->Current, 1);
        currentPlayer = this->Players[current];
    } while (!currentPlayer.Active);
    this->Current = current;
}

// necessary??
void Game::getBet(const int& pid, const int& amount) {

}

void Game::resolveBet(const int& pid) {
    Seat player = this->getSeat(pid);
    
    int bet = player.Bet;
    
    player.Bet = 0;
    player.PotSplit += bet;
    this->Pot += bet;
}

void Game::resolveBet(const int& pid, const int& amount) {
    Seat player = this->getSeat(pid);

    player.Cash -= amount;
    player.PotSplit += amount;
    this->Pot += amount;
}

struct Seat Game::getSeat(const int& pid) {
    // quick jailbreak in case pid = seat number in vector
    int numPlayers = this->Players.size();
    if (pid < numPlayers && this->Players[pid].PlayerId == pid) {
        return this->Players[pid];
    } else {
        for (int i = 0; i < numPlayers; i++) {
            Seat player = this->Players[i];
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
    this->TheDeck.refillCards();

    this->MaxSeats = settings.MaxSeats;
    this->SmallSize = settings.SmallBlind;
    this->BigSize = settings.BigBlind;

    for (int id : PlayerIds) {
        struct Seat seat = {
            id,
            true,
            settings.StartingCash,
            0,
            0
        };

        this->Players.push_back(seat);
        this->Hands.push_back(Hand{});
    }

    this->advanceGame();
}

struct PublicState Game::getPublicState() {
    PublicState state = {
        this->Players,
        this->GameStage,
        this->Current,
        this->SmallBlind,
        this->Pot,
        this->CurrentBet,
        this->Community
    };

    return state;
}

bool Game::submitAction(const Action& action) {
    int pid = action.PlayerId;
    Stage stage = this->GameStage;

    if (pid != this->Current || stage == INACTIVE) {
        return false;
    }

    ActionTypes type = action.Type;
    int amount = action.Amount;

    // todo: add stages


    return true;
}