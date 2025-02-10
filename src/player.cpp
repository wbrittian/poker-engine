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

Action Player::getAction(int bet) {
    string response;
    
    while (true) {
        cout << "Enter your action, type h for help > ";
        cin >> response;

        if (response == "h") {
            cout << "Actions:" 
            << endl << "call -> calls current bet or checks if bet is 0"
            << endl << "bet -> raises the bet (raise amount must be at least current bet)"
            << endl << "h -> shows the help menu"
            << endl;
        } else if (response == "call") {
            return {CALL, 0};
        } else if (response == "raise") {
            string amt;
            cin >> amt;

            if (amt == "all") {
                return {RAISE, this->Cash};
            } else if (true) { // isInteger(amt)
                int val = stoi(amt);

                if (val >= bet) {
                    return {RAISE, val};
                } else {
                    cout << "raise must be >= current bet" << endl;
                }
            } else {
                cout << "bet amount must be an integer" << endl;
            }
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