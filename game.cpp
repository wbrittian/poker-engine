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

void Game::initializeGame(Player& player, int numBots, int startingCash) {
    this->Deck.refillCards();

    this->addPlayer(player);

    // add bots
    for (int i = 0; i < numBots; i++) {
        string name = "Bot " + to_string(i + 1);

        this->addPlayer(Bot(name, startingCash));
    }
}

void Game::newRound() {
    this->Deck.refillCards();
    this->Pot = 0;

}

void Game::addPlayer(Player player) {
    this->Players.push_back(player);
}

void Game::removePlayer(Player* player) {
    int idx = this->findPlayerIndex(player);
    this->Players.erase(this->Players.begin() + idx);
}

// TODO: fix function based on player structure
// currently findPlayerIndex won't work if player has been 
// removed from game already
void Game::moveBlinds() {
    int bigIdx = this->findPlayerIndex(this->BigBlind);

    if (bigIdx + 1 == this->Players.size()) {
        this->SmallBlind = &this->Players[bigIdx];
        this->BigBlind = &this->Players[0];
    } else if (bigIdx + 1 > this->Players.size()) {
        
    } else {
        this->SmallBlind = &this->Players[bigIdx];
        this->BigBlind = &this->Players[bigIdx + 1];
    }
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
// misc
//
int Game::findPlayerIndex(Player* player) {
    auto idx = find(this->Players.begin(), this->Players.end(), *player);

    if (idx != this->Players.end()) {
        return distance(this->Players.begin(), idx);
    } else {
        throw range_error("Player not found");
    }
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