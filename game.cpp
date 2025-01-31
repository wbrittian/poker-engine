/*game.cpp*/

//
// a poker game
//
// William Brittian
// 2025
//

#include "game.h"

void Game::initializeGame(int numPlayers, int startingCash) {
    this->Deck.refillCards();

    for (int i = 0; i < numPlayers; i++) {
        this->addPlayer(Player(startingCash));
    }
}

void Game::addPlayer(Player player) {
    this->Players.push_back(player);
}

void Game::dealToPlayer(Player& player) {
    player.emptyHand();
    player.addCards(this->Deck.drawCards(2));
}