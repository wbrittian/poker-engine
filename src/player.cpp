/*player.cpp*/

//
// a player
//
// William Brittian
// 2025
//

#include "player.h"

void Player::emptyHand() {
    this->Cards.clear();
}

void Player::addCards(vector<Card> cards) {
    for (Card card : cards) {
        this->Cards.push_back(card);
    }
}

void Player::editCash(int amount) {
    this->Cash += amount;
}

void Player::setNextPlayer(Player* player) {
    this->Next = player;
}

Action Player::getAction(Game* game) {
    int bet = game->getBet();
    
}

void Player::printCards() {
    this->Cards[0].printCard(true);
    cout << " ";
    this->Cards[1].printCard(true);
    cout << endl;
}

//
// accessors
//
vector<Card> Player::getCards() {
    return this->Cards;
}

int Player::getCash() {
    return this->Cash;
}

string Player::getName() {
    return this->Name;
}

Player* Player::getNextPlayer() {
    return this->Next;
}

int Player::getBet() {
    return this->Bet;
}

int Player::getPotSplit() {
    return this->PotSplit;
}