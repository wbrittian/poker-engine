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
    Action action;
    while (true) {
        string cmd;
        cout << "Enter your action, type h for help > ";
        cin >> cmd;

        if (cmd == "q") {
            action.Type = QUIT;
            break;
        } else if (cmd == "h") {
           cout << "Available round active commands:"
            << endl << "h -> get list of available commands"
            << endl << "q -> quit the game"
            << endl << "c -> call the current bet or check"
            << endl << "b/r [AMOUNT] -> bet (or raise) the given amount"
            << endl << "f -> fold your hand"
            << endl << "s -> print scoreboard"
            << endl;
        } else if (cmd == "c") {
            action.Type = CALL;
            break;
        } else if (cmd == "b" || cmd == "r") {
            string amt;
            cin >> amt;

            if (amt == "all") {
                action = {BET, Cash};
                break;
            } else if (true) { // isInteger(amt)
                int val = stoi(amt);

                if (val >= bet) {
                    action = {BET, val};
                    break;
                } else {
                    cout << "raise must be >= current bet" << endl;
                }
            } else {
                cout << "bet amount must be an integer" << endl;
            }
        } else if (cmd == "f") {
            action.Type = FOLD;
            break;
        }
    }
    return action;
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