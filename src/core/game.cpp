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
void Game::takeBlinds() {
    this->Round += 1;

    int small = this->SmallBlind;
    int big = getPlayer(1, small);

    this->resolveBet(small, this->SmallSize);
    this->resolveBet(big, this->BigSize);

    this->CurrentBet = this->BigSize;
    this->Current = this->getPlayer(2, small);
}

int Game::getPlayer(const int& n) {
    return (this->Current + n) % this->Players.size();
}

int Game::getPlayer(const int& point, const int& n) {
    return (point + n) % this->Players.size();
}

void Game::moveCurrent() {
    Seat currentPlayer;
    do {
        this->Current = this->getPlayer(1);
        currentPlayer = this->Players[this->Current];
    } while (!currentPlayer.Active);
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
    this->Deck.refillCards();

    this->MaxSeats = settings.MaxSeats;
    this->SmallSize = settings.SmallBlind;
    this->BigSize = settings.BigBlind;

    for (int id : PlayerIds) {
        struct Seat seat = {
            id,
            false,
            settings.StartingCash,
            0,
            0
        };

        this->Players.push_back(seat);
    }

    this->takeBlinds();
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