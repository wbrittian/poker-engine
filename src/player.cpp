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