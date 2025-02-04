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

void Game::initializeGame(Player* player, int numBots, int startingCash) {
    this->Deck.refillCards();

    this->User = player;
    this->addPlayer(player, nullptr);
    player->setNextPlayer(player);

    // add bots
    for (int i = 0; i < numBots; i++) {
        string name = "Bot " + to_string(numBots - i);

        this->addPlayer(new Bot(name, startingCash), player);
    }

    this->NumPlayers = 1 + numBots;
}

void Game::finishGame() {
    
    

}

void Game::newRound() {
    this->Deck.refillCards();

    // TODO: implement main game loop
}

void Game::settleRound() {
    // TODO: implement code for determining winner

    this->Bet = 0;
    this->Pot = 0;
}

void Game::addPlayer(Player* player, Player* position) {
    if (position == nullptr) {
        this->FirstPlayer = player;
    } else {
        Player* temp = position->getNextPlayer();
        position->setNextPlayer(player);
        player->setNextPlayer(temp);
    }
}

void Game::removePlayer(Player* player) {

    if (player->getNextPlayer() != player) {
        Player* previous = this->getPreviousPlayer(player);
        Player* next = player->getNextPlayer();

        previous->setNextPlayer(next);
    }
    
    delete player;
}

// rotates the head pointer to the next in the order
// head by default points to the small blind
void Game::rotateOrder() {
    this->FirstPlayer = this->FirstPlayer->getNextPlayer();
}


//
// round active functions
//

void Game::settlePlayerBet(int amount, Player* player) {
    if (this->Bet + amount < 0 ||
        player->getCash() - amount < 0) {
        throw range_error("Negative value error");
    }

    player->editCash(-amount);
    this->Bet += amount;
}

void Game::settlePlayerPot(int amount, Player* player) {
    if (this->Pot + amount < 0 || 
        player->getCash() - amount < 0) {
        throw range_error("Negative value error");
    }

    player->editCash(-amount);
    this->Pot += amount;
}

void Game::settleBetPot(int amount) {
    this->Bet -= amount;
    this->Pot += amount;
}

void Game::dealToPlayer(Player* player) {
    player->emptyHand();
    player->addCards(this->Deck.drawCards(2));
}


//
// misc
//
Player* Game::getNthPlayer(int N) {

}

// returns the player behind the given player in the order
Player* Game::getPreviousPlayer(Player* player) {
    Player* current = player;

    while (current->getNextPlayer() != player) {
        current = current->getNextPlayer();
    }

    return current;
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

Player* Game::getCurrentLeader() {
    
}