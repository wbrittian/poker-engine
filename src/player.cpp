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

void Player::setBet(int amount) {
    this->Bet = amount;
}

void Player::editBet(int amount) {
    this->Bet += amount;
}

void Player::resetBet() {
    this->Bet = 0;
}

void Player::editPotSplit(int amount) {
    this->PotSplit += amount;
}

void Player::resetPotSplit() {
    this->PotSplit = 0;
}

void Player::setNextPlayer(shared_ptr<Player> player) {
    this->Next = player;
}

Action Player::getAction(int bet) {
    string response;
    
    while (true) {
        cout << "Enter your action, type h for help > ";
        cin >> response;

        if (response == "h") {
            cout << "Actions:" 
            << endl << "c -> calls current bet or checks if bet is 0"
            << endl << "b/r amount -> raises the bet (raise amount must be at least current bet)"
            << endl << "f -> folds your hand"
            << endl << "h -> shows the help menu"
            << endl;
        } else if (response == "c") {
            return {CALL, 0};
        } else if (response == "b" || response == "r") {
            string amt;
            cin >> amt;

            if (amt == "all") {
                return {BET, this->Cash};
            } else if (true) { // isInteger(amt)
                int val = stoi(amt);

                if (val >= bet) {
                    return {BET, val};
                } else {
                    cout << "raise must be >= current bet" << endl;
                }
            } else {
                cout << "bet amount must be an integer" << endl;
            }
        } else if (response == "f") {
            return {FOLD, 0};
        }
    }
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

string Player::getName() {
    return this->Name;
}

shared_ptr<Player> Player::getNextPlayer() {
    return this->Next;
}

int Player::getCash() {
    return this->Cash;
}

int Player::getBet() {
    return this->Bet;
}

int Player::getPotSplit() {
    return this->PotSplit;
}