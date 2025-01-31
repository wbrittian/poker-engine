/*game.cpp*/

//
// a poker game
//
// William Brittian
// 2025
//

#include "game.h"


//
// general game state functions
//

void Game::initializeGame(int numPlayers, int startingCash) {
    this->Deck.refillCards();

    for (int i = 0; i < numPlayers; i++) {
        this->addPlayer(Player(startingCash));
    }
}

void Game::newRound() {
    this->Deck.refillCards();
    this->Pot = 0;

}

void Game::addPlayer(Player player) {
    this->Players.push_back(player);
}


//
// round active functions
//

void Game::settlePlayerBet(int amount, Player& player) {
    if (this->Bet + amount < 0 ||
        player.getCash() - amount < 0) {
        throw range_error("Negative value error");
    }

    player.editCash(-amount);
    this->Bet += amount;
}

void Game::settlePlayerPot(int amount, Player& player) {
    if (this->Pot + amount < 0 || 
        player.getCash() - amount < 0) {
        throw range_error("Negative value error");
    }

    player.editCash(-amount);
    this->Pot += amount;
}

void Game::settleBetPot(int amount) {
    this->Bet -= amount;
    this->Pot += amount;
}

void Game::dealToPlayer(Player& player) {
    player.emptyHand();
    player.addCards(this->Deck.drawCards(2));
}


//
// accessors
//
int Game::getPot() {
    return this->Pot;
}

int Game::getBet() {
    return this->Bet;
}